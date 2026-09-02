// target-lowering.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only target-lowering.cpp

// target-lowering.cpp
//
// The custom-lowering pieces the chapter prints separately: registering the operation,
// declaring a target's own SelectionDAG node, routing an operation to it from
// LowerOperation, and building the replacement in LowerMUL. None of them compiles
// alone -- MyTargetISD, MyTargetLowering and the SelectionDAG headers are all
// somewhere else in each case.
//
// LowerFormalArguments is not here. As printed its parameter list is literally
// `(...)`, an ellipsis standing in for the real signature, so it is pseudo-code and
// there is no file it could be an excerpt of.
#include "llvm/ADT/APInt.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

// One custom node, named for what the hardware does. The chapter used to declare
// MUL_LoHi here and then call MyTargetISD::MUL16x16 from LowerMUL a few paragraphs
// later -- two names for one node, only one of them declared. MUL_LoHi was also the
// wrong name: in LLVM's own vocabulary SMUL_LOHI and UMUL_LOHI return *both* halves of
// a double-width product, whereas this node returns a single i32.
//
// In a real target this enum belongs in MyArchISelLowering.h, not the .cpp: TableGen
// writes the literal token MyTargetISD::MUL16x16 into MyArchGenDAGISel.inc, which is
// included into the selector class in MyArchISelDAGToDAG.cpp, and that file cannot see
// a type declared in a different translation unit.
namespace MyTargetISD {
enum NodeType {
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  MUL16x16
};
} // namespace MyTargetISD

// Derived from TargetLowering, so `override` is checked. The chapter's definitions
// omitted the trailing const on LowerOperation, which meant they did not override the
// virtual at all -- they quietly became new member functions the SelectionDAG
// machinery never calls, and a reader would get a target that builds and does nothing.
class MyTargetLowering : public TargetLowering {
public:
  MyTargetLowering(const TargetMachine &TM, const TargetSubtargetInfo &STI);

  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  SDValue LowerMUL(SDValue Op, SelectionDAG &DAG) const;
};

// Registering the operation is what makes any of the rest run. Every operation
// defaults to Legal, so without the Custom action the legalizer never calls
// LowerOperation for ISD::MUL and selection fails outright.
//
// Marking MUL Custom is necessary but not sufficient. When a custom lowering declines,
// legalization continues to Expand, and ExpandNode's MUL case reaches for SMUL_LOHI --
// which also defaults to Legal, so the multiply would be rewritten into an operation
// this target has no instruction for. The four wide-multiply forms are therefore
// Expanded explicitly.
MyTargetLowering::MyTargetLowering(const TargetMachine &TM,
                                   const TargetSubtargetInfo &STI)
    : TargetLowering(TM, STI) {
  setOperationAction(ISD::MUL,       MVT::i32, Custom);
  setOperationAction(ISD::SMUL_LOHI, MVT::i32, Expand);
  setOperationAction(ISD::UMUL_LOHI, MVT::i32, Expand);
  setOperationAction(ISD::MULHS,     MVT::i32, Expand);
  setOperationAction(ISD::MULHU,     MVT::i32, Expand);
}

SDValue MyTargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::MUL:
    return LowerMUL(Op, DAG);
  default:
    return SDValue();
  }
}

// The premise: this ISA has no 32-bit multiply, only a 16x16 -> 32 unit.
//
// LowerMUL must therefore return a value for every multiply, not only for the ones it
// finds convenient. An earlier version returned an empty SDValue when it could not
// prove the operands were narrow, on the reasoning that the default expansion would
// take over. There is no such default here: declining sends legalization on to Expand,
// which rewrites the multiply into SMUL_LOHI, and from there to a __mulsi3 libcall
// that a target outside LLVM's known-architecture list cannot resolve. The compile
// ends in "no libcall available for mul" rather than in working code.
//
// The general case is three products. Writing a = ah:al and b = bh:bl,
//
//     a * b == al*bl + ((al*bh + ah*bl) << 16)   (mod 2^32)
//
// The ah*bh term contributes only from bit 32 upwards, so it drops out of a 32-bit
// result. The narrow case is kept as a fast path on top of that, not instead of it.
SDValue MyTargetLowering::LowerMUL(SDValue Op, SelectionDAG &DAG) const {
  SDLoc DL(Op);
  EVT VT = Op.getValueType();
  unsigned Bits = VT.getSizeInBits();
  unsigned Half = Bits / 2;
  SDValue LHS = Op.getOperand(0);
  SDValue RHS = Op.getOperand(1);

  // Fast path: both operands provably fit in the low half, so one 16x16 does it.
  APInt HiHalf = APInt::getHighBitsSet(Bits, Half);
  if (DAG.MaskedValueIsZero(LHS, HiHalf) && DAG.MaskedValueIsZero(RHS, HiHalf))
    return DAG.getNode(MyTargetISD::MUL16x16, DL, VT, LHS, RHS);

  SDValue Mask = DAG.getConstant(maskTrailingOnes<uint64_t>(Half), DL, VT);
  SDValue Shift = DAG.getShiftAmountConstant(Half, VT, DL);
  SDValue AL = DAG.getNode(ISD::AND, DL, VT, LHS, Mask);
  SDValue AH = DAG.getNode(ISD::SRL, DL, VT, LHS, Shift);
  SDValue BL = DAG.getNode(ISD::AND, DL, VT, RHS, Mask);
  SDValue BH = DAG.getNode(ISD::SRL, DL, VT, RHS, Shift);

  SDValue LoLo = DAG.getNode(MyTargetISD::MUL16x16, DL, VT, AL, BL);
  SDValue AlBh = DAG.getNode(MyTargetISD::MUL16x16, DL, VT, AL, BH);
  SDValue AhBl = DAG.getNode(MyTargetISD::MUL16x16, DL, VT, AH, BL);
  SDValue Mid = DAG.getNode(ISD::ADD, DL, VT, AlBh, AhBl);
  Mid = DAG.getNode(ISD::SHL, DL, VT, Mid, Shift);
  return DAG.getNode(ISD::ADD, DL, VT, LoLo, Mid);
}
