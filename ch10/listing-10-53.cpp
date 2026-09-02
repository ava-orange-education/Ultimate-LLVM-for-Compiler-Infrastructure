// Listing 10-53. Inserting before a block's terminator
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-53.cpp

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

// Building at the end of a block puts the new instruction *after* the branch that
// ends it, which is not a valid block. Constructing the builder from the block's
// terminator inserts before that branch, which is what is almost always meant.
Value *insertBeforeTerminator(BasicBlock *BB, Value *X, Value *Y) {
  IRBuilder<> Builder(BB->getTerminator());
  return Builder.CreateMul(X, Y, "product");
}
