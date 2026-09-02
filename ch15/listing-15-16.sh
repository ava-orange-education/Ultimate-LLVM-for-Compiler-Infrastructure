# Listing 15-16. Querying build flags with llvm-config
# Run: bash listing-15-16.sh

# # Get LLVM version
llvm-config --version

# # Get compilation flags
llvm-config --cppflags

# # Get linking flags
llvm-config --ldflags --libs core support

# # Get available components
llvm-config --components
