// Listing 7-8. Legacy: declaring what the pass preserves
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-7-08.cpp

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Pass.h"

using namespace llvm;

struct MyFunctionPass : public FunctionPass {
  static char ID;
  MyFunctionPass() : FunctionPass(ID) {}

  // Declare analysis usage and preservation.
  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<DominatorTreeWrapperPass>();     // Needs dominator tree.
    AU.addPreserved<LoopInfoWrapperPass>();         // Loop info remains valid.
    AU.setPreservesCFG();                           // CFG is not modified.
  }

  bool runOnFunction(Function &F) override {
    // Retrieve the already computed dominator tree.
    auto &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
    (void)DT;
    // Return true if the IR was modified; the pass manager will then invalidate
    // any analyses not marked as preserved. A comment cannot stand in for the
    // expression here, so the placeholder is a value the reader replaces.
    bool IRModified = false;
    return IRModified;
  }
};
