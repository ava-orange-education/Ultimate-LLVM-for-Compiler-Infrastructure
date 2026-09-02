# Listing 1-14. Linking two bitcode files into one module
# Run: bash listing-1-14.sh

llvm-link file1.bc file2.bc -o combined.bc
