# Listing 13-42. The passes that take MLIR down to LLVM
# Run: bash listing-13-42.sh

mlir-opt prog.mlir \
  --convert-scf-to-cf \
  --finalize-memref-to-llvm \
  --convert-arith-to-llvm \
  --convert-func-to-llvm \
  --convert-math-to-llvm \
  --convert-cf-to-llvm \
  --reconcile-unrealized-casts
