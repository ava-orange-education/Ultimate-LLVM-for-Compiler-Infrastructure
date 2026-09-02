// Listing 7-10. Tracing a pass with LLVM_DEBUG
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-7-10.cpp

#include "llvm/IR/Dominators.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "my-pass"

using llvm::dbgs;

struct MyPass : public llvm::PassInfoMixin<MyPass> {
  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
    LLVM_DEBUG(dbgs() << "Running MyPass on function: " << F.getName() << "\n");

    // Retrieve an analysis result lazily.
    auto &DT = FAM.getResult<llvm::DominatorTreeAnalysis>(F);
    LLVM_DEBUG(dbgs() << "Dominator Tree for " << F.getName() << ":\n");
    DT.print(dbgs());
    // run() must return: nothing here changes the IR.
    return llvm::PreservedAnalyses::all();
  }
};
