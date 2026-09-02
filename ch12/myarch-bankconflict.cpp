// myarch-bankconflict.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only myarch-bankconflict.cpp

//===-- MyArchBankConflictAvoider.cpp - a MachineFunctionPass ---*- C++ -*-===//
//
// Replacement for Chapter 12, "Extending and Customizing the Backend" --
// the bank-conflict-avoidance pass, printed across two listings.
//
// What was wrong with the printed version:
//
//   struct MyArchBankConflictAvoider : MachineFunctionPass {
//     bool runOnMachineFunction(MachineFunction &MF) override { ... }
//   };
//   FunctionPass *llvm::createMyArchBankConflictAvoider() {
//     return new MyArchBankConflictAvoider();
//   }
//
// The class definition on its own compiles. The factory does not, and this is
// the defect: MachineFunctionPass has no default constructor -- it is
// MachineFunctionPass(char &ID) -- so the implicit default constructor of the
// subclass is deleted and `new MyArchBankConflictAvoider()` is ill-formed:
//
//   error: call to implicitly-deleted default constructor of
//          'MyArchBankConflictAvoider'
//   note: base class 'MachineFunctionPass' has no default constructor
//
// Every LLVM pass therefore declares `static char ID;`, passes it to the base
// constructor, and defines it once at namespace scope. The pass ID is LLVM's
// RTTI: its address, not its value, identifies the pass to the PassManager.
//
// Verified with clang++ 22.1.8 -fsyntax-only against the real headers.
//
//===----------------------------------------------------------------------===//

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

namespace llvm {
FunctionPass *createMyArchBankConflictAvoider();
} // namespace llvm

FunctionPass *llvm::createMyArchBankConflictAvoider() {
  return new MyArchBankConflictAvoider();
}
