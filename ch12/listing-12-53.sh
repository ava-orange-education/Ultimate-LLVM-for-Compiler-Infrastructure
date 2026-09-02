# Listing 12-53. Assembling to an object file with llvm-mc
# Run: bash listing-12-53.sh

llvm-mc -triple=myarch-unknown-elf -filetype=obj output.s -o temp.o
llvm-objdump -d temp.o
