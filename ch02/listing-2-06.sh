# Listing 2-6. Cloning the SPIR-V translator alongside LLVM
# Run: bash listing-2-06.sh

git clone https://github.com/llvm/llvm-project.git .
git clone https://github.com/KhronosGroup/SPIRV-LLVM-Translator.git
git clone https://github.com/intel/opencl-clang.git
git clone https://github.com/KhronosGroup/SPIRV-Headers.git ./llvm/projects/SPIRV-Headers
git clone https://github.com/intel/vc-intrinsics.git ./llvm/projects/vc-intrinsics
