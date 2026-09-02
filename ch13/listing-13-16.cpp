// Listing 13-16. Creating a function and building its body
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-16.cpp

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"

using namespace mlir;

// Three steps: create the function, move the insertion point inside it, then build.
void addBody(OpBuilder &builder, Location loc, FunctionType type, Value a, Value b) {
  auto func = func::FuncOp::create(builder, loc, "add", type);
  builder.setInsertionPointToStart(func.addEntryBlock());
  Value sum = arith::AddIOp::create(builder, loc, a, b);
  func::ReturnOp::create(builder, loc, sum);
}
