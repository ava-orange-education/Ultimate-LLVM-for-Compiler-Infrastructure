# Listing 12-54. Disassembling the encoded bytes
# Run: bash listing-12-54.sh

llvm-mc -disassemble -triple=myarch -mcpu=... < binary.o
