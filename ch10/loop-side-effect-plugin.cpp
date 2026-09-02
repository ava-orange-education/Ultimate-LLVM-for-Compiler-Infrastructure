// loop-side-effect-plugin.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only loop-side-effect-plugin.cpp

// loop-side-effect-plugin.cpp
//
// The pass plugin the chapter builds across listings 10-3, 10-4, 10-6, 10-9 and 10-15:
// an analysis that records what each loop does to memory, a transform that marks the
// loops with side effects, and the registration that makes both reachable from opt.
// Each listing prints one piece, so none of them compiles alone.
//
// The plugin-registration listing (10-6) is deliberately NOT here. It needs
// llvm/Plugins/PassPlugin.h. That header moved out of Passes/ between 18 and 22; the
// harness cannot compile any plugin entry point in this environment either, which is
// why 10-6 sits at INCONCLUSIVE-FRAGMENT. Including it would make this file
// unbuildable and every pairing against it worthless, so it stays out and 10-6 stays
// unpaired until a tree with that header is available.
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"

using namespace llvm;

// What the analysis reports about one loop.
struct LoopSideEffectInfo {
  bool hasMemoryWrite = false;
  bool hasVolatileAccess = false;
  bool hasFunctionCallWithSideEffects = false;
};

// The analysis itself. AnalysisInfoMixin supplies the plumbing the new pass manager
// needs; the Key is what the manager uses to tell one analysis from another.
struct LoopSideEffectAnalysis : AnalysisInfoMixin<LoopSideEffectAnalysis> {
    using Result = DenseMap<const Loop *, LoopSideEffectInfo>;
    Result run(Function &F, FunctionAnalysisManager &AM);
private:
    static AnalysisKey Key;
    friend AnalysisInfoMixin<LoopSideEffectAnalysis>;
};

// The parameter is named FAM here, not AM. The book declares it as AM above and then
// uses FAM throughout the body, which does not compile -- there is no FAM in scope.
LoopSideEffectAnalysis::Result
LoopSideEffectAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  Result SideEffects;
  LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);
  AAResults &AA = FAM.getResult<AAManager>(F);

  for (Loop *L : LI.getLoopsInPreorder()) {
    LoopSideEffectInfo Info;
    for (BasicBlock *BB : L->blocks()) {
      for (Instruction &I : *BB) {
        if (isa<StoreInst>(&I)) {
          Info.hasMemoryWrite = true;
        }
        if (I.mayReadOrWriteMemory() && I.isVolatile()) {
          Info.hasVolatileAccess = true;
        }
        if (auto *CI = dyn_cast<CallBase>(&I)) {
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
AnalysisKey LoopSideEffectAnalysis::Key;

static void attachLoopMetadata(BranchInst *BI, LLVMContext &Ctx) {
  // A loop id has to be distinct, and its first operand has to be the node itself.
  // MDNode::get uniques its result and the node built here had no self-reference,
  // so Loop::getLoopID() rejected it and the metadata was silently ignored -- the
  // pass appeared to work and marked nothing.
  MDNode *Marker = MDNode::getDistinct(
      Ctx, {nullptr, MDString::get(Ctx, "llvm.loop.has_side_effects")});
  Marker->replaceOperandWith(0, Marker);
  BI->setMetadata("llvm.loop", Marker);
}

// The transform that consumes the analysis.
struct LoopEffectMarkerPass : PassInfoMixin<LoopEffectMarkerPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
      auto &LoopEffects = FAM.getResult<LoopSideEffectAnalysis>(F);
      LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);

      for (Loop *L : LI.getLoopsInPreorder()) {
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

struct LoopSideEffectAnalysisPrinterPass
    : PassInfoMixin<LoopSideEffectAnalysisPrinterPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    return LoopEffectMarkerPass().run(F, FAM);
  }
};

// A loop pass, to show the nesting in listing 10-15.
struct LoopSideEffectTagger : PassInfoMixin<LoopSideEffectTagger> {
  PreservedAnalyses run(Loop &L, LoopAnalysisManager &AM,
                        LoopStandardAnalysisResults &AR, LPMUpdater &U) {
    return PreservedAnalyses::all();
  }
};

void build_nested_pipeline(ModulePassManager &Out) {
  LoopPassManager LPM;
  LPM.addPass(LoopSideEffectTagger());

  FunctionPassManager FPM;
  FPM.addPass(createFunctionToLoopPassAdaptor(std::move(LPM)));

  ModulePassManager MPM;
  MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
  Out = std::move(MPM);
}
