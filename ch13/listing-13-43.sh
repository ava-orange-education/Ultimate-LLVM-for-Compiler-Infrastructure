# Listing 13-43. Emitting the LLVM IR file
# Run: bash listing-13-43.sh

mlir-translate --mlir-to-llvmir final.mlir -o final.ll
