#include "LoopSideEffectAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/MemorySSA.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

AnalysisKey LoopSideEffectAnalysis::Key;

LoopSideEffectAnalysis::Result
LoopSideEffectAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  Result SideEffects;

  LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);
  AAResults &AA = FAM.getResult<AAManager>(F);

  for (Loop *L : LI) {
    LoopSideEffectInfo Info;

    for (BasicBlock *BB : L->blocks()) {
      for (Instruction &I : *BB) {
        if (auto *SI = dyn_cast<StoreInst>(&I)) {
          Info.hasMemoryWrite = true;
        } else if (I.mayReadOrWriteMemory() && I.isVolatile()) {
          Info.hasVolatileAccess = true;
        } else if (auto *CI = dyn_cast<CallBase>(&I)) {
          auto ME = AA.getMemoryEffects(CI);
          if (!ME.doesNotAccessMemory()) {
            Info.hasFunctionCallWithSideEffects = true;
          }
        }
      }
    }

    SideEffects[L] = Info;
  }

  return SideEffects;
}


// extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
//   return {
//     LLVM_PLUGIN_API_VERSION, "LoopEffectMarkerPass", LLVM_VERSION_STRING,
//     [](PassBuilder &PB) {

//       PB.registerPipelineParsingCallback(
//         [](StringRef Name, FunctionPassManager &FPM,
//            ArrayRef<PassBuilder::PipelineElement>) {
//           if (Name == "loop-effect-printer") {
//             FPM.addPass(LoopSideEffectAnalysisPrinterPass());
//             return true;
//           }
//           return false;
//         });

//       PB.registerAnalysisRegistrationCallback(
//         [](FunctionAnalysisManager &FAM) {
//           FAM.registerPass([] { return LoopSideEffectAnalysis(); });
//         });

//     PB.registerPipelineStartEPCallback([](ModulePassManager &MPM,
//           OptimizationLevel Level) {

//         FunctionPassManager FPM;
//         FPM.addPass(LoopSideEffectAnalysisPrinterPass());
//         MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
//         });
//     }
//   };
// }