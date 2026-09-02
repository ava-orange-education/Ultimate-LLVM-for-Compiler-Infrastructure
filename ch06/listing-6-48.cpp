// Listing 6-48. Adding a block and pointing the builder at it
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-6-48.cpp

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

using namespace llvm;

void addEntryBlock(LLVMContext &Context, IRBuilder<> &Builder, Function *Function) {
  llvm::BasicBlock *EntryBlock = llvm::BasicBlock::Create(Context, "entry", Function);
  Builder.SetInsertPoint(EntryBlock);
}
