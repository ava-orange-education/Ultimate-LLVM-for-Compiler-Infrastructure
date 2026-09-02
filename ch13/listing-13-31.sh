# Listing 13-31. Removing the redundancy with canonicalize and cse
# Run: bash listing-13-31.sh

mlir-opt simple.mlir -canonicalize -cse
