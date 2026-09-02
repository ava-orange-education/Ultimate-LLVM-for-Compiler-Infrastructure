// mul16x16-pattern.td -- the complete file.
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . mul16x16-pattern.td -o /dev/null

// The 16x16 -> 32 multiply: the custom DAG node, the instruction, and the pattern
// that ties them together.
//
// Three things are needed and the chapter previously showed only two. A custom node
// created in C++ with DAG.getNode(MyTargetISD::MUL16x16, ...) cannot be selected until
// TableGen is told the node exists -- that is what the SDNode record below does. Its
// string argument is the C++ enumerator, spelled exactly.
//
// The unit is unsigned: it reads both operands as values in [0, 65535]. That is the
// only reading consistent with how LowerMUL feeds it -- the fast path admits operands
// only after proving their high half is zero, and the general path hands it halves
// produced by AND and SRL, both zero-extended. A signed 16x16 unit would give a
// different answer for an operand in [0x8000, 0xFFFF], which passes that guard.
//
// Checked with:
//   llvm-tblgen --print-records -I candidates/ch12/book -I <llvm>/include \
//       mul16x16-pattern.td
//   llvm-tblgen -gen-dag-isel  ... (against a scratch file that includes MyArch.td)
include "MyArchInstrInfo.td"

// SDTIntBinOp is the standard profile for a two-operand integer arithmetic node:
// one result and two operands, all the same integer type.
def myarch_mul16x16 : SDNode<"MyTargetISD::MUL16x16", SDTIntBinOp>;

// The instruction carries no Pattern of its own. Giving it [(set i32:$rd, (mul ...))]
// would let ISel select it straight from a generic 32-bit mul, which is exactly what
// must not happen: the hardware multiplies 16 bits by 16 bits, and only LowerMUL knows
// whether one such product is the whole answer or one of the three that make it.
def MUL16x16 : MyArchInst<0b100000, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
                          "mul16x16 $rd, $rs1, $rs2", []>;

// Selection happens from the custom node, not from `mul`.
def : Pat<(myarch_mul16x16 i32:$a, i32:$b),
          (MUL16x16 GPR:$a, GPR:$b)>;
