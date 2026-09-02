// Listing 7-4. A pass in the legacy pass manager
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-7-04.cpp

#include "llvm/Pass.h"

using namespace llvm;

struct MyLegacyPass : public FunctionPass {
  static char ID;
  MyLegacyPass() : FunctionPass(ID) {}
  // ...
};
