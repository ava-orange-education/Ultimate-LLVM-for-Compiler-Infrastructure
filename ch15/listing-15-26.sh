# Listing 15-26. Reducing a crashing input with bugpoint
# Run: bash listing-15-26.sh

# # 1. Find crash with bugpoint
bugpoint --compile-custom --compile-command="./my-tool.sh" crash.ll

# # 2. Symbolize addresses in crashes
export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
ASAN_OPTIONS=symbolize=1 ./my-program

# # 3. Run comprehensive sanitizer testing
clang -fsanitize=address,undefined,fuzzer test.c -o test-all
./test-all
