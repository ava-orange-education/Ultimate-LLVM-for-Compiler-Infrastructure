# Listing 15-23. A fast development build with Ninja
# Run: bash listing-15-23.sh

cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DLLVM_USE_LINKER=lld \
  -DLLVM_OPTIMIZED_TABLEGEN=ON
