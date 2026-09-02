# Listing 13-20. Canonicalising, then unrolling an affine loop
# Run: bash listing-13-20.sh

mlir-opt input.mlir --pass-pipeline="builtin.module(canonicalize,func.func(affine-loop-unroll))"
