# Listing 7-1. Running opt with a pipeline or an -O level
# Run: bash listing-7-01.sh

# ; provide custom pass pipeline
opt -passes=<pipeline> input.ll -S
# ; provide default optimization levels such as O1, O2, ...
opt -O2 input.ll -S
