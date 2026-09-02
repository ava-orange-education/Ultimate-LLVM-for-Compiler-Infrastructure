// Listing 10-33. The same update, printed a second time in this section
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-33.cpp

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"

using namespace llvm;

// Incremental update: cheaper, and what a well-behaved pass does.
void updateIncrementally(DominatorTree &DT, LoopInfo &LI, BasicBlock *NewBB,
                         BasicBlock *NewIDom, Loop *L) {
  DT.splitBlock(NewBB);
  DT.changeImmediateDominator(NewBB, NewIDom);
  L->addBasicBlockToLoop(NewBB, LI);
}

// The blunt alternative: throw both away and rebuild. Correct, but it costs a
// full recomputation, so it is a last resort rather than a habit.
void recomputeFromScratch(Function &F, DominatorTree &DT, LoopInfo &LI) {
  DT.recalculate(F);
  LI.releaseMemory();
  LI.analyze(DT);
}
