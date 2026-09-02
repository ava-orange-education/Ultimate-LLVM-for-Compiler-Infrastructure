// Listing 10-5. A printer pass that reports what it found
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-05.cpp

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// A printer pass under the new pass manager: no base class to inherit, just
// PassInfoMixin for the boilerplate, and a run() with the right signature.
struct LoopSideEffectPrinterPass
    : PassInfoMixin<LoopSideEffectPrinterPass> {

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);

    for (Loop *L : LI)
      errs() << "loop with header " << L->getHeader()->getName() << "\n";

    // A printer changes nothing, so every analysis survives it.
    return PreservedAnalyses::all();
  }
};
