// Listing 10-12. The marker pass in full
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-12.cpp

#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

struct LoopEffectMarkerPass : PassInfoMixin<LoopEffectMarkerPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    return PreservedAnalyses::all();
  }
};

// The name the pipeline parser matches has to be the name a reader will type on
// the opt command line, and the pass it constructs has to be the struct declared
// above -- a mismatch between the two compiles and then silently never runs.
void registerPasses(PassBuilder &PB) {
  PB.registerPipelineParsingCallback(
      [](StringRef Name, FunctionPassManager &FPM,
         ArrayRef<PassBuilder::PipelineElement>) {
        if (Name == "loop-effect-marker") {
          FPM.addPass(LoopEffectMarkerPass());
          return true;
        }
        return false;
      });
}
