# Listing 7-13. Saving optimization remarks to a file
# Run: bash listing-7-13.sh

clang -O2 -fsave-optimization-record -c input.ll
# This will generate file input.opt.yaml, which contains detailed information about the optimization applied.
