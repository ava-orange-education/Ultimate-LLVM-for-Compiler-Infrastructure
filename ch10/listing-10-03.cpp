// Listing 10-3. The result struct the loop side-effect analysis returns
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-03.cpp

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

struct LoopSideEffectInfo {
  bool hasMemoryWrite = false;
  bool hasVolatileAccess = false;
  bool hasFunctionCallWithSideEffects = false;
};

struct LoopSideEffectAnalysis : AnalysisInfoMixin<LoopSideEffectAnalysis> {
    using Result = DenseMap<const Loop *, LoopSideEffectInfo>;
    Result run(Function &F, FunctionAnalysisManager &AM);
private:
    static AnalysisKey Key;
    friend AnalysisInfoMixin<LoopSideEffectAnalysis>;
};
