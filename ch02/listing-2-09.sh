# Listing 2-9. The whole build, start to finish
# Run: bash listing-2-09.sh

git clone https://github.com/llvm/llvm-project.git
cd llvm-project
mkdir build
cd build
cmake -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_TARGET_ARCH=arm \
    -DLLVM_TARGETS_TO_BUILD=ARM \
    -DCMAKE_C_COMPILER=/usr/bin/arm-linux-gnueabihf-gcc \
    -DCMAKE_CXX_COMPILER=/usr/bin/arm-linux-gnueabihf-g++ \
    -DCMAKE_SYSROOT=/path/to/arm-sysroot \
    ../llvm
make -j$(nproc)
