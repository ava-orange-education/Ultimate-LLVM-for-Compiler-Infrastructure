// Listing 10-31. Splitting it and keeping the analyses correct
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-31.cpp

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

// Split OldBB at SplitInst, keeping the analyses correct as we go.
BasicBlock *split(BasicBlock *OldBB, Instruction *SplitInst,
                  DominatorTree &DT, LoopInfo &LI) {
  // SplitBlock updates the DominatorTree and LoopInfo itself when they are
  // passed in -- doing it by hand afterwards is how they drift out of step.
  BasicBlock *NewBB = SplitBlock(OldBB, SplitInst, &DT, &LI, nullptr);

  // If OldBB was in a loop, NewBB belongs to the same one. SplitBlock has
  // already done this; it is shown here because a hand-built split must.
  if (Loop *L = LI.getLoopFor(OldBB))
    if (!LI.getLoopFor(NewBB))
      L->addBasicBlockToLoop(NewBB, LI);

  return NewBB;
}
