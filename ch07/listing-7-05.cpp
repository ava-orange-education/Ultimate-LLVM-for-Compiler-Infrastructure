// Listing 7-5. The same pass in the new pass manager
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-7-05.cpp

#include "llvm/IR/PassManager.h"

struct MyNewPass : public llvm::PassInfoMixin<MyNewPass> {
  // ...
};
