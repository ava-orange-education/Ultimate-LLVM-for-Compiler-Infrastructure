// Listing 10-42. Inserting before a given instruction
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-42.cpp

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;

// Constructed from an instruction, the builder inserts *before* it.
Value *insertBeforeInstruction(Instruction *Where, Value *A, Value *B) {
  IRBuilder<> Builder(Where);
  // The name is an ordinary string literal. Word's curly quotes are not
  // quotation marks to a compiler.
  return Builder.CreateAdd(A, B, "sum");
}

// Constructed from a block, it inserts at the end -- usually not what is wanted,
// so build it at the terminator to land before the branch.
Value *insertBeforeTerminator(BasicBlock *BB, Value *X, Value *Y) {
  IRBuilder<> Builder(BB->getTerminator());
  return Builder.CreateMul(X, Y, "product");
}
