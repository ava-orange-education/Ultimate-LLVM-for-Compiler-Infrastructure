# Listing 15-13. Turning an address into a source location
# Run: bash listing-15-13.sh

# # Symbolize address
llvm-symbolizer --obj=program 0x4008b3

# # Symbolize with context lines
llvm-symbolizer --obj=program --print-source-context-lines=3 0x4008b3

# # Set symbolizer for sanitizers
export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
ASAN_OPTIONS=symbolize=1 ./program
