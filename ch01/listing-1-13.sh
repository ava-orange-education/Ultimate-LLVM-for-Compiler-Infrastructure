# Listing 1-13. Naming individual passes instead of a preset pipeline
# Run: bash listing-1-13.sh

opt -passes='inline,simplifycfg' llvm-demo.bc -o llvm-demo-opt.bc
