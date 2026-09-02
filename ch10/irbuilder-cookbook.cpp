// irbuilder-cookbook.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only irbuilder-cookbook.cpp

// irbuilder-cookbook.cpp
//
// Where an IRBuilder puts what it builds, where types come from, and how a new
// instruction keeps the debug location of the one it replaces. The chapter prints
// these as single lines; they need a builder, a block and a context to mean anything.
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace {
void builder_placement(Function &F, DominatorTree *DT, LoopInfo *LI) {
  BasicBlock *SomeBasicBlock = &F.getEntryBlock();
  BasicBlock *OldBB = SomeBasicBlock;
  Instruction *SplitInst = &*SomeBasicBlock->getFirstInsertionPt();

  // Insert immediately before the terminator rather than after it: appending after a
  // terminator would leave the block with two, which the verifier rejects.
  IRBuilder<> Builder(&SomeBasicBlock->back()); // insert before last instruction

  // Pointing the builder at a block appends to the end of it.
  Builder.SetInsertPoint(SomeBasicBlock);

  // Types belong to a context, and every value in a module shares one. Taking the
  // context from the function guarantees the type matches the values it will be used
  // with; a second LLVMContext would produce types that compare unequal.
  LLVMContext &Ctx = F.getContext();  // or M.getContext();
  Type *IntTy = Type::getInt32Ty(Ctx);
  (void)IntTy;

  // Splitting hands back the new block and keeps the analyses up to date.
  BasicBlock *NewBB = SplitBlock(OldBB, SplitInst, DT, LI, nullptr);
  (void)NewBB;
}

void carry_debug_location(Instruction *I, Instruction *Original) {
  // A replacement instruction with no location makes the line it came from vanish
  // from the debugger; copying it across keeps stepping accurate.
  I->setDebugLoc(Original->getDebugLoc());
}
} // namespace
