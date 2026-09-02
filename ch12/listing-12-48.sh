# Listing 12-48. Compiling for the new target with llc
# Run: bash listing-12-48.sh

llc -march=myarch input.ll -o output.s
