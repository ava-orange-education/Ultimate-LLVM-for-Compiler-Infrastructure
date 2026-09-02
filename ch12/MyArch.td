// MyArch.td -- the complete file.
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . MyArch.td -o /dev/null

// The top-level file pulls in the rest of the target. TableGen has no include
// guards, so the files form a chain -- each one includes the file before it --
// and MyArch.td only has to include the last link:
//
//   MyArchRegisterInfo.td <- MyArchInstrInfo.td <- MyArchCallingConv.td
//                         <- MyArchSubtarget.td <- MyArch.td
include "MyArchSubtarget.td"

// Assembly printing
def MyArchAsmWriter : AsmWriter {
  let AsmWriterClassName = "InstPrinter";
  let PassSubtarget = 1;
  let Variant = 0;
}

// The target itself. Target is a plain class whose fields are set in the body:
// it takes no template arguments and no dag. TableGen discovers the registers,
// instructions and sub-target features by scanning the records defined above,
// so the target record only names its instruction set and assembly writers.
def MyArchInstrInfo : InstrInfo;

def MyArch : Target {
  let InstructionSet  = MyArchInstrInfo;
  let AssemblyWriters = [MyArchAsmWriter];
}
