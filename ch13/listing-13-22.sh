# Listing 13-22. Lowering and running in one pipeline
# Run: bash listing-13-22.sh

mlir-opt input.mlir --convert-scf-to-cf | mlir-runner --entry-point-result=void --shared-libs=libmlir_runner_utils.so
