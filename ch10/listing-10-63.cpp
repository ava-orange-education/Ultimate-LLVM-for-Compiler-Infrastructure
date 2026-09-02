// Listing 10-63. Reporting what a pass preserved
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-63.cpp

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

// A pass does not invalidate analyses by hand. It reports what it preserved, and
// the analysis manager works out what has to be thrown away.
PreservedAnalyses runAndInvalidateEverything(Function &F,
                                             FunctionAnalysisManager &FAM) {
  // ... transform F ...

  // Returning none() tells the manager the IR changed enough that nothing can
  // be trusted; returning all() after changing the CFG is the classic bug.
  return PreservedAnalyses::none();
}
