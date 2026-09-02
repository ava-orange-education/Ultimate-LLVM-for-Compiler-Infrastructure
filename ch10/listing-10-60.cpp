// Listing 10-60. Removing the incoming value along with the edge
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-60.cpp

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/SSAUpdater.h"

using namespace llvm;

// Removing a predecessor means removing its incoming value too, or the PHI is
// left with an entry for a block that no longer branches here and the verifier
// rejects the function.
void dropPredecessor(PHINode *Phi, BasicBlock *OldBB) {
  Phi->removeIncomingValue(OldBB, /*DeletePHIIfEmpty=*/true);
}

// Building new PHIs by hand is rarely necessary: SSAUpdater works out where they
// are needed and inserts them.
Value *rebuildValue(Type *Ty, BasicBlock *BB1, Value *V1,
                    BasicBlock *BB2, Value *V2, BasicBlock *SomeBB) {
  SSAUpdater Updater;
  Updater.Initialize(Ty, "new_var");
  Updater.AddAvailableValue(BB1, V1);
  Updater.AddAvailableValue(BB2, V2);
  return Updater.GetValueAtEndOfBlock(SomeBB);
}
