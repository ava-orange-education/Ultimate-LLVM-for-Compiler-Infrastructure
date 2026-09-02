include "MyArchRegisterInfo.td"

// A 16-bit signed immediate operand.
def simm16 : Operand<i32>;

// Base instruction format: a 32-bit instruction word laid out as a 6-bit
// opcode followed by three 5-bit register fields.
//
//   31    26 25  21 20  16 15  11 10        0
//  +--------+------+------+------+-----------+
//  | opcode |  rd  | rs1  | rs2  |  unused   |
//  +--------+------+------+------+-----------+
class MyArchInst<bits<6> opcode, dag outs, dag ins, string asmstr,
                 list<dag> pattern> : Instruction {
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

  let Inst{31-26} = opcode;
  let Inst{25-21} = rd;
  let Inst{20-16} = rs1;
  let Inst{15-11} = rs2;
  let Inst{10-0}  = 0;
}

// Register-register form.
class ALUrr<bits<6> opcode, string mnemonic, SDNode op>
    : MyArchInst<opcode, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
                 mnemonic # " $rd, $rs1, $rs2",
                 [(set i32:$rd, (op i32:$rs1, i32:$rs2))]>;

// Register-immediate form: the immediate takes the place of the rs2 field and
// occupies the low half of the instruction word.
class ALUri<bits<6> opcode, string mnemonic, SDNode op>
    : MyArchInst<opcode, (outs GPR:$rd), (ins GPR:$rs1, simm16:$imm),
                 mnemonic # "i $rd, $rs1, $imm",
                 [(set i32:$rd, (op i32:$rs1, imm:$imm))]> {
  bits<16> imm;
  let rs2 = 0;
  let Inst{15-0} = imm;
}

// Add register to register, and add immediate to register.
def ADDrr : ALUrr<0b000001, "add", add>;
def ADDri : ALUri<0b010001, "add", add>;

// The patterns above are attached to the instructions themselves, so no extra
// Pat<> records are needed for plain add. An explicit Pat is only required when
// the DAG node and the instruction do not line up one-to-one.
