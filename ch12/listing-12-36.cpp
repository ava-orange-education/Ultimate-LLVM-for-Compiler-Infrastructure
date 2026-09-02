// Listing 12-36. The headers a MachineFunctionPass needs
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-12-36.cpp

#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/Pass.h"

using namespace llvm;

// Target-specific helpers, defined elsewhere in the MyArch backend.
static bool isBankConflicting(const MachineInstr &MI);
static void transform(MachineInstr &MI);

namespace {

struct MyArchBankConflictAvoider : MachineFunctionPass {
  static char ID;

  MyArchBankConflictAvoider() : MachineFunctionPass(ID) {}

  StringRef getPassName() const override {
    return "MyArch bank conflict avoider";
  }

  bool runOnMachineFunction(MachineFunction &MF) override {
    bool Changed = false;
    for (MachineBasicBlock &MBB : MF)
      for (MachineInstr &MI : MBB)
        if (isBankConflicting(MI)) {
          transform(MI);
          Changed = true;
        }
    // Return whether anything changed, so the PassManager can preserve
    // analyses when it did not. The printed version always returned true.
    return Changed;
  }
};

} // end anonymous namespace

char MyArchBankConflictAvoider::ID = 0;
