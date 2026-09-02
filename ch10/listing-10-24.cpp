// Listing 10-24. Hoisting an instruction to a common dominator
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-24.cpp

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;

// Move Inst to the nearest block that dominates both B1 and B2.
void hoist(DominatorTree &DT, BasicBlock *B1, BasicBlock *B2, Instruction *Inst) {
  BasicBlock *Dominator = DT.findNearestCommonDominator(B1, B2);

  // BasicBlock::getInstList() is private as of LLVM 22.1.8 -- the instruction
  // list is no longer reachable from outside. Instructions move themselves:
  Inst->moveBefore(Dominator->getTerminator()->getIterator());
}
