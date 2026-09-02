// Listing 13-37. Applying a pattern set greedily
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-37.cpp

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

using namespace mlir;

struct FoldAddZero;   // defined alongside, see the pattern listing

LogicalResult runPatterns(func::FuncOp function) {
  MLIRContext *context = function.getContext();

  RewritePatternSet patterns(context);
  // patterns.add<FoldAddZero>(context);

  // applyPatternsAndFoldGreedily is deprecated in favour of applyPatternsGreedily;
  // the driver folds as it goes either way.
  return applyPatternsGreedily(function, std::move(patterns));
}
