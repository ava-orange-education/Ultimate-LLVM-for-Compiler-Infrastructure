# Listing 13-44. Running the result through the JIT
# Run: bash listing-13-44.sh

mlir-runner prog.mlir \
  -e main --entry-point-result=void \
  --shared-libs=libmlir_c_runner_utils.so
