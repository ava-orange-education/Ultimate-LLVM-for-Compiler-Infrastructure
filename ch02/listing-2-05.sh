# Listing 2-5. Configuring an LLVM build with CMake
# Run: bash listing-2-05.sh

cmake -G "Unix Makefiles" ../llvm-project/llvm \
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
      -DLLVM_TARGETS_TO_BUILD=X86 \
      -DCMAKE_BUILD_TYPE=Release
