// Listing 13-26. A pass that walks the operations it lowers
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-13-26.cpp

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"

using namespace mlir;

// MLIR has had no FunctionPass since the pass infrastructure was reworked: a pass
// is parameterised on the operation it runs over. The hooks changed with it --
// runOnFunction/getFunction became runOnOperation/getOperation.
struct LowerMyMatmulPass
    : public PassWrapper<LowerMyMatmulPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(LowerMyMatmulPass)

  StringRef getArgument() const final { return "lower-mydsl-matmul"; }
  StringRef getDescription() const final {
    return "Lower mydsl.matmul to linalg.matmul";
  }

  void runOnOperation() override {
    getOperation().walk([](Operation *op) {
      // Match mydsl::MatmulOp here and replace it, usually through a
      // RewritePattern rather than by hand.
    });
  }
};

// Registration is a namespace-scope object, so it needs a name.
static PassRegistration<LowerMyMatmulPass> registration;
