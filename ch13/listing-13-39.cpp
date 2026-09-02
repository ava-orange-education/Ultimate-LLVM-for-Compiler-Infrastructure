// Listing 13-39. Declaring which operations the conversion may leave
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-39.cpp

#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Transforms/DialectConversion.h"

using namespace mlir;

// A conversion target says what is allowed to survive: the driver keeps rewriting
// until nothing illegal is left, and reports failure if it cannot get there.
void configureTarget(MLIRContext &context) {
  ConversionTarget target(context);

  target.addLegalDialect<linalg::LinalgDialect>();
  // target.addIllegalOp<mydsl::MatmulOp>();   // the dialect this chapter defines
}
