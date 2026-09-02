// Listing 10-41. Walking the loops of a function
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-41.cpp

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
using namespace llvm;

unsigned countInstructionsInInnerLoops(Function &F, LoopInfo &LI) {
  unsigned Count = 0;
  // getLoopsInPreorder walks the whole nest. Iterating LoopInfo directly visits only
  // top-level loops, so an inner loop's stores would be attributed to its outermost
  // parent and the inner loop would never get an entry of its own.
  for (Loop *L : LI.getLoopsInPreorder()) {

    for (Loop *SubLoop : depth_first(L)) {
      if (SubLoop->getSubLoops().empty()) {
        for (BasicBlock *BB : SubLoop->blocks()) {
          for (Instruction &I : *BB) {
            if (!I.isDebugOrPseudoInst()) {
              ++Count;
            }
          }
        }
      }
    }
  }
  return Count;
}
