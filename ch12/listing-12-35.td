// Listing 12-35. A format class that fixes the encoding once
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-35.td -o /dev/null

include "MyArchRegisterInfo.td"

// A custom format class fixes the encoding once so each instruction that uses
// it only supplies its opcode, operands, syntax and pattern. Every template
// argument needs a type -- TableGen has no untyped parameters -- and the four
// operand fields below are the ones Instruction actually declares.
class MyRType<bits<6> opc, dag outs, dag ins, string asmstr, list<dag> pattern>
    : Instruction {
  field bits<32> Inst;

  let Namespace = "MyArch";
  let Size = 4;

  dag OutOperandList = outs;
  dag InOperandList  = ins;
  let AsmString = asmstr;
  let Pattern   = pattern;

  bits<5> rd;
  bits<5> rs1;
  bits<5> rs2;

  let Inst{31-26} = opc;
  let Inst{25-21} = rd;
  let Inst{20-16} = rs1;
  let Inst{15-11} = rs2;
  let Inst{10-0}  = 0;
}

def ANDrr : MyRType<0b000011, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
                    "and $rd, $rs1, $rs2",
                    [(set i32:$rd, (and i32:$rs1, i32:$rs2))]>;
