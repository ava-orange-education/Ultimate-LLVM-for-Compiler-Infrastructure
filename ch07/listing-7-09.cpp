// Listing 7-9. New: requesting an analysis and abandoning it
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-7-09.cpp

#include "llvm/IR/Dominators.h"
#include "llvm/IR/PassManager.h"

struct MyNewPass : public llvm::PassInfoMixin<MyNewPass> {
  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
    // Lazy evaluation: request the dominator tree only when needed.
    auto &DT = FAM.getResult<llvm::DominatorTreeAnalysis>(F);
    (void)DT;

    bool Modified = false;
    // ... perform transformations on F ...
    // Determine whether the IR is modified (set Modified appropriately).

    // Start with the assumption that all analyses are preserved.
    llvm::PreservedAnalyses PA = llvm::PreservedAnalyses::all();
    if (Modified) {
      // Now, if the transformation touches areas that affect the dominator tree,
      // then explicitly abandon that analysis. PreservedAnalyses has no
      // invalidate(): abandon() is how a single analysis is dropped from an
      // otherwise-preserved set.
      PA.abandon<llvm::DominatorTreeAnalysis>();
      // However, if the transformation leaves the control-flow intact, one might omit this.
    }
    return PA;
  }
};
