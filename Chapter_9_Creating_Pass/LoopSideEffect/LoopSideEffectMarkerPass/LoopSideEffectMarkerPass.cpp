#include "LoopSideEffectAnalysis.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

void attachLoopMetadata(BranchInst *BI, LLVMContext &Context) {
  // Metadata string tag
  MDString *Key = MDString::get(Context, "loop.has.sideeffects");

  // Create a metadata node: !{!"loop.has.sideeffects"}
  MDNode *LoopMD = MDNode::get(Context, {Key});

  // Wrap in another node as required by !llvm.loop
  MDNode *LoopAnnotation = MDNode::getDistinct(Context, {LoopMD});

  // Attach to branch instruction
  BI->setMetadata("llvm.loop", LoopAnnotation);
}

struct LoopEffectMarkerPass : public PassInfoMixin<LoopEffectMarkerPass> {
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

      if (Info.hasMemoryWrite || Info.hasFunctionCallWithSideEffects) {
        BasicBlock *Header = L->getHeader();
        if (BranchInst *BI = dyn_cast<BranchInst>(Header->getTerminator())) {
          attachLoopMetadata(BI, BI->getContext());
        }
      }
    }

    return PreservedAnalyses::all();
  }
};

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "LoopEffectMarkerPass", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "loop-effect-marker") {
            FPM.addPass(LoopEffectMarkerPass());
            return true;
          }
          return false;
        });
      
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "loop-effect-printer") {
            FPM.addPass(LoopSideEffectAnalysisPrinterPass());
            return true;
          }
          return false;
        });

      PB.registerAnalysisRegistrationCallback(
        [](FunctionAnalysisManager &FAM) {
          FAM.registerPass([] { return LoopSideEffectAnalysis(); });
        });
    }
  };
}
