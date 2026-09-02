// Listing 12-13. The register's assembly name
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-13.td -o /dev/null

include "llvm/Target/Target.td"
// harness shim: minimal target so instruction/register fragments can be parsed
def HarnessInstrInfo : InstrInfo;
def HarnessTarget : Target { let InstructionSet = HarnessInstrInfo; }

def RAX : Register<"rax">;
def RBX : Register<"rbx">;
