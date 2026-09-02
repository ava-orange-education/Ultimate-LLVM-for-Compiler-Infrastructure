// Listing 10-45. Naming the value a builder creates
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-45.cpp

#include "llvm/IR/IRBuilder.h"

using namespace llvm;

// The third argument names the result. It is an ordinary string literal --
// the curly quotes Word inserts are not quotation marks to a compiler.
Value *scale(IRBuilder<> &Builder, Value *X, Value *Y) {
  return Builder.CreateMul(X, Y, "scaled_val");
}
