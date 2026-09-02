# Listing 15-6. Building a fuzz target with libFuzzer
# Run: bash listing-15-06.sh

# # Compile with fuzzing and address sanitizer
clang++ -g -fsanitize=fuzzer,address fuzz_target.cc -o fuzzer
