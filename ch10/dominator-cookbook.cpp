// dominator-cookbook.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only dominator-cookbook.cpp

// dominator-cookbook.cpp
//
// The dominator-tree queries the chapter shows one at a time: fetching the tree inside
// a pass, asking whether one block dominates another, using that to drop a redundant
// check, finding a loop's preheader, and instrumenting every return. Each is printed
// as a bare if-statement because each answers one question, but none of them compiles
// without a DominatorTree in scope -- so this is the pass they come from.
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace {
struct DominatorCookbook : PassInfoMixin<DominatorCookbook> {

  // Fetching the tree. The analysis manager computes it on demand and caches it.
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);
    PostDominatorTree &PDT = FAM.getResult<PostDominatorTreeAnalysis>(F);

    // Use DT here
    LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);
    BasicBlock *ConditionBlock = &F.getEntryBlock();
    BasicBlock *ReturnBlock = &F.back();
    BasicBlock *TrueConditionBlock = ConditionBlock;
    BasicBlock *TargetBlock = ReturnBlock;
    BasicBlock *BB = ConditionBlock;
    BasicBlock *CheckBlock = ConditionBlock;
    // The block the cleanup lives in. Post-dominance asks whether control is
    // certain to arrive here, whichever way it leaves the block being tested.
    BasicBlock *CleanupBB = nullptr;
    for (BasicBlock &B : F)
      if (isa<ReturnInst>(B.getTerminator()))
        CleanupBB = &B;
    Function *LogFn = F.getParent()->getFunction("log_return");

    // A dominates B: every path to B passes through A first.
    if (DT.dominates(ConditionBlock, ReturnBlock)) {
      // It's safe to assume the condition is always checked before returning.
    }

    // The same query is what licenses removing a repeated test.
    if (DT.dominates(TrueConditionBlock, TargetBlock)) {
      // Remove unnecessary branches or checks in TargetBlock
    }

    // A preheader is the single predecessor outside the loop, and it dominates the
    // header -- which is what makes it the safe place to hoist to.
    if (Loop *L = LI.getLoopFor(BB)) {
      BasicBlock *Preheader = L->getLoopPreheader();
      if (Preheader && DT.dominates(Preheader, L->getHeader())) {
        // Insert transformations safely before the loop starts
      }
    }

    // Instrumenting the returns that a given check dominates.
    if (LogFn) {
      for (BasicBlock &BB : F) {
        if (isa<ReturnInst>(BB.getTerminator())) {
          // CleanupBB post-dominates BB when every path leaving BB reaches it, so
          // whatever BB acquires is certain to be released there. DT.dominates
          // would answer the opposite question: what has already run before BB.
          if (CleanupBB && PDT.dominates(CleanupBB, &BB)) {
            IRBuilder<> Builder(&*BB.getFirstInsertionPt());
            Builder.CreateCall(LogFn);
          }
        }
      }
    }

    return PreservedAnalyses::all();
  }
};
} // namespace
