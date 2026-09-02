// Listing 10-8. Declaring the transformation pass
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-08.cpp

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

struct LoopEffectMarkerPass: PassInfoMixin<LoopEffectMarkerPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
};
