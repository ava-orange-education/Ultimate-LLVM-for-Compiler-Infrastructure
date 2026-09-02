// Listing 13-28. A rewrite pattern that folds a constant
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-28.cpp

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/PatternMatch.h"

using namespace mlir;

// Fold `x + 0` to `x`. A pattern receives the rewriter; it never edits the IR
// directly, so that the driver can track what changed.
struct FoldAddZero : public OpRewritePattern<arith::AddIOp> {
  using OpRewritePattern<arith::AddIOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(arith::AddIOp op,
                                PatternRewriter &rewriter) const override {
    auto rhs = op.getRhs().getDefiningOp<arith::ConstantIntOp>();
    if (!rhs || rhs.value() != 0)
      return failure();

    // Replace the operation with its own left operand.
    rewriter.replaceOp(op, op.getLhs());
    return success();
  }
};
