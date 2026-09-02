# Listing 12-31. Assembling one instruction and reading the bytes back
# Run: bash listing-12-31.sh

# # Textual assembly
llvm-mc -arch=x86_64 -filetype=asm foo.s

# # Binary object
llvm-mc -arch=x86_64 -filetype=obj foo.s -o foo.o
