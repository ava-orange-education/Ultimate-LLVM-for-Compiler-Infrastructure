// Listing 12-29. Writing the instruction encoding field by field
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-29.td -o /dev/null

include "llvm/Target/Target.td"

// There is no record that attaches an encoding to an instruction from outside.
// InstructionEncoding is a base class Instruction already inherits -- it is what
// provides the Inst field -- so the encoding is written inside the instruction
// definition, by assigning the bits of the instruction word:
class ExampleInst<bits<6> opcode, dag outs, dag ins, string asmstr>
    : Instruction {
  field bits<32> Inst;

  let Namespace = "MyArch";
  let Size = 4;

  dag OutOperandList = outs;
  dag InOperandList  = ins;
  let AsmString = asmstr;

  bits<5> rd;
  bits<5> rs;

  let Inst{31-26} = opcode;   // the opcode field
  let Inst{25-21} = rd;       // destination register
  let Inst{20-16} = rs;       // source register
  let Inst{15-0}  = 0;
}

// Anything the bit assignments cannot express -- x86's ModR/M byte, say -- is
// emitted by the target's own MCCodeEmitter instead.
