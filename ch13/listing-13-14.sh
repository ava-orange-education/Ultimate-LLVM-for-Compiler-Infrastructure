# Listing 13-14. Canonicalising and CSE-ing a file with mlir-opt
# Run: bash listing-13-14.sh

mlir-opt input.mlir -canonicalize -cse
