# Listing 15-25. From C to optimised IR, end to end
# Run: bash listing-15-25.sh

# # 1. Create LLVM IR from C
clang -S -emit-llvm test.c -o test.ll

# # 2. Run optimization passes
opt -passes="mem2reg,instcombine" test.ll -S -o test-opt.ll

# # 3. Test with FileCheck
opt -passes="instcombine" test.ll -S | FileCheck test.ll

# # 4. Fuzz the optimized code
clang -fsanitize=fuzzer,address test-opt.ll -o fuzzer
./fuzzer

# # 5. Profile-guided optimization
clang -fprofile-instr-generate test.c -o test-profile
LLVM_PROFILE_FILE="test.profraw" ./test-profile
llvm-profdata merge -output=test.profdata test.profraw
clang -fprofile-instr-use=test.profdata test.c -o test-optimized
