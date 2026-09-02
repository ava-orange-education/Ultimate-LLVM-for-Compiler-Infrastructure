// Listing 15-22. Tracing and asserting inside a pass
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-15-22.cpp

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

#define DEBUG_TYPE "my-pass"
void checkAndTrace(Function &F, Instruction *I) {
#ifndef NDEBUG
  if (verifyFunction(F, &errs()))
    llvm_unreachable("Function verification failed");
#endif
  LLVM_DEBUG(dbgs() << "Processing: " << *I << '\n');
}
