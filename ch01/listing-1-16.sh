# Listing 1-16. Retargeting the same bitcode at ARM
# Run: bash listing-1-16.sh

llc llvm-demo.bc -march=arm -o llvm-demo-arm.s
