#ifndef LLVM_LOOP_SIDE_EFFECT_ANALYSIS_H
#define LLVM_LOOP_SIDE_EFFECT_ANALYSIS_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/MemoryLocation.h"

namespace llvm {

struct LoopSideEffectInfo {
  bool hasMemoryWrite = false;
  bool hasVolatileAccess = false;
  bool hasFunctionCallWithSideEffects = false;
};

class LoopSideEffectAnalysis : public AnalysisInfoMixin<LoopSideEffectAnalysis> {
public:
  using Result = DenseMap<const Loop *, LoopSideEffectInfo>;

  Result run(Function &F, FunctionAnalysisManager &FAM);

  static AnalysisKey Key;
};

class LoopSideEffectAnalysisPrinterPass : public PassInfoMixin<LoopSideEffectAnalysisPrinterPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    auto &LoopEffects = FAM.getResult<LoopSideEffectAnalysis>(F);
    LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);

    for (Loop *L : LI) {
      auto InfoIt = LoopEffects.find(L);
      if (InfoIt == LoopEffects.end()) continue;

      const LoopSideEffectInfo &Info = InfoIt->second;
      errs() << "Loop in function " << F.getName() << ":\n";
      if (Info.hasMemoryWrite) errs() << "  - Writes to memory\n";
      if (Info.hasVolatileAccess) errs() << "  - Has volatile access\n";
      if (Info.hasFunctionCallWithSideEffects) errs() << "  - Calls with side effects\n";
    }

    return PreservedAnalyses::all();
  }
};

} // namespace llvm

#endif
