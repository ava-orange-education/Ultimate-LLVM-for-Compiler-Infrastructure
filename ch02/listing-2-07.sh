# Listing 2-7. Configuring a cross build for ARM
# Run: bash listing-2-07.sh

cmake -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_TARGET_ARCH=arm \
    -DLLVM_TARGETS_TO_BUILD=ARM \
    -DCMAKE_C_COMPILER=/path/to/your/arm-compiler \
    -DCMAKE_CXX_COMPILER=/path/to/your/arm-cxx-compiler \
    -DCMAKE_SYSROOT=/path/to/your/sysroot \
    ../llvm
