// Listing 13-45. Building a function with OpBuilder
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-45.cpp

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"

using namespace mlir;

// Build `func @add() -> i32 { return 2 + 3 }` programmatically.
func::FuncOp buildAdd(MLIRContext *context) {
  OpBuilder builder(context);
  Location loc = builder.getUnknownLoc();

  Type i32Type = builder.getIntegerType(32);
  auto funcType = builder.getFunctionType({}, {i32Type});

  // Since LLVM 21 the preferred spelling is OpTy::create(builder, ...) rather
  // than builder.create<OpTy>(...); both still work at 22.1.8.
  auto func = func::FuncOp::create(builder, loc, "add", funcType);
  builder.setInsertionPointToStart(func.addEntryBlock());

  Value a = arith::ConstantOp::create(builder, loc, builder.getI32IntegerAttr(2));
  Value b = arith::ConstantOp::create(builder, loc, builder.getI32IntegerAttr(3));
  Value sum = arith::AddIOp::create(builder, loc, a, b);

  func::ReturnOp::create(builder, loc, sum);
  return func;
}
