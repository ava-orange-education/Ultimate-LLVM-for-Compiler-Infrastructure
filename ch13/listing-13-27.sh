# Listing 13-27. Loading the pass as a plugin
# Run: bash listing-13-27.sh

mlir-opt myprog.mlir \
  --load-pass-plugin=./libMyDSLPasses.so \
  --pass-pipeline="builtin.module(func.func(lower-mydsl-matmul))"
