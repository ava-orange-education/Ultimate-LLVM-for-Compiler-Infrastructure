# Listing 12-56. Measuring instruction latency with llvm-exegesis
# Run: bash listing-12-56.sh

llvm-exegesis -target=myarch -opcode-name=MUL16x16 -mode=latency
