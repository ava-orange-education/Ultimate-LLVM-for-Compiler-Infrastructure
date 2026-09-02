// Listing 10-35. Finding a store nothing reads
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-35.cpp

#include "llvm/Analysis/MemorySSA.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

// Is this store dead? Ask MemorySSA who reads from it.
bool tryRemoveDeadStore(MemorySSA *MSSA, StoreInst *SI) {
  MemoryAccess *StoreAccess = MSSA->getMemoryAccess(SI);
  if (!StoreAccess)
    return false;

  for (User *U : StoreAccess->users())
    if (isa<MemoryUse>(U))
      return false;            // something reads it; it has to stay

  SI->eraseFromParent();
  return true;
}
