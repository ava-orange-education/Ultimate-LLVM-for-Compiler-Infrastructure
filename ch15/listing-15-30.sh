# Listing 15-30. The profile-guided optimisation pipeline
# Run: bash listing-15-30.sh

# Complete PGO pipeline
clang -fprofile-instr-generate program.c -o program-instrumented
LLVM_PROFILE_FILE="program.profraw" ./program-instrumented
llvm-profdata merge -output=program.profdata program.profraw
clang -fprofile-instr-use=program.profdata program.c -o program-optimized
