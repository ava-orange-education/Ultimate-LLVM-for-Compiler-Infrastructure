# Listing 13-40. A pass pipeline written out in full
# Run: bash listing-13-40.sh

mlir-opt myprog.mlir \
  --load-pass-plugin=./libMyDSLPasses.so \
  --pass-pipeline="builtin.module(canonicalize,cse,func.func(mydsl-lowering),convert-scf-to-cf,finalize-memref-to-llvm,convert-func-to-llvm,reconcile-unrealized-casts)"
