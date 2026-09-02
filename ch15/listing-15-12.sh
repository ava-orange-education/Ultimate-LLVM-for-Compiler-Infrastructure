# Listing 15-12. Assembling IR with llvm-as
# Run: bash listing-15-12.sh

# # Convert assembly to bitcode
llvm-as program.ll  # Creates program.bc

# # Output to specific file
llvm-as -o output.bc input.ll
