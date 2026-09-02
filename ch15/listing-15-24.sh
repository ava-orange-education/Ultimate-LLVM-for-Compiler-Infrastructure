# Listing 15-24. Cutting link time with split DWARF
# Run: bash listing-15-24.sh

cmake -DLLVM_USE_SPLIT_DWARF=ON \
  -DLLVM_PARALLEL_LINK_JOBS=1
