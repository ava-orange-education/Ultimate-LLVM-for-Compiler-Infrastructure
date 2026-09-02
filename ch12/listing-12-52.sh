# Listing 12-52. Stopping after register allocation to inspect machine IR
# Run: bash listing-12-52.sh

llc -mtriple=x86_64-unknown-linux-gnu -stop-after=greedy input.ll -o func.mir
