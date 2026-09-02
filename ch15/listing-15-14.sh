# Listing 15-14. Collecting a profile with instrumentation
# Run: bash listing-15-14.sh

# # Step 1: Compile with instrumentation
clang -fprofile-instr-generate program.c -o program

# # Step 2: Run program to collect profile
LLVM_PROFILE_FILE="program.profraw" ./program

# # Step 3: Convert raw profile to indexed format
llvm-profdata merge -output=program.profdata program.profraw

# # Step 4: Compile with profile data
clang -fprofile-instr-use=program.profdata program.c -o program_optimized
