# Listing 15-11. Disassembling bitcode with llvm-dis
# Run: bash listing-15-11.sh

# # Convert bitcode to assembly
llvm-dis program.bc  # Creates program.ll

# # Read from stdin
llvm-dis < input.bc > output.ll
