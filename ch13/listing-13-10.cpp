// Listing 13-10. Building the same addition through the C++ API
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-10.cpp

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Builders.h"

using namespace mlir;

// The same addition the textual IR above writes as `%sum = arith.addi %a, %b : i32`,
// built through the C++ API instead. Since LLVM 21 the preferred spelling is
// OpTy::create(builder, ...); builder.create<OpTy>(...) still works at 22.1.8.
Value buildAdd(OpBuilder &builder, Location loc, Value a, Value b) {
  return arith::AddIOp::create(builder, loc, a, b);
}
