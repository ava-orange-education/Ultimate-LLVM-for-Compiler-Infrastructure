// legacy-dominator-pass.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only legacy-dominator-pass.cpp

// legacy-dominator-pass.cpp
//
// The chapter introduces the legacy pass manager by building one pass across two
// listings: first getAnalysisUsage, which declares what the pass needs and what it
// leaves intact, then runOnFunction, which collects the result. Both are printed as
// bare member functions, so this is the class they belong to.
//
// It is kept apart from legacy-analysis-pass.cpp because that one returns a named
// IRModified flag -- the reviewer asked for an expression a reader could replace
// rather than a comment -- while these two listings show the read-only case that
// returns false outright.
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {
struct DominatorReadingPass : public FunctionPass {
  static char ID;
  DominatorReadingPass() : FunctionPass(ID) {}

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    // 'addRequired' tells the pass manager that a dominator tree must be
    // available prior to running this pass.
    AU.addRequired<DominatorTreeWrapperPass>();
    // If our pass does not modify control-flow graph (CFG), we can declare it:
    AU.setPreservesCFG();
  }

  bool runOnFunction(Function &F) override {
    // Retrieve the analysis result; if it hasn't been computed yet,
    // the pass manager computes it before running this pass.
    auto &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();

    // Use the dominator tree info to perform transformation or to guide analysis.
    // For example, we might want to verify that a certain block is dominated
    // by another block, thus ensuring safe code motion.
    (void)DT;

    // In this example, we make no modifications.
    return false;
  }
};
} // namespace

char DominatorReadingPass::ID = 0;
static RegisterPass<DominatorReadingPass>
    X("legacy-dominator-reading", "Reads the dominator tree without changing the IR");
