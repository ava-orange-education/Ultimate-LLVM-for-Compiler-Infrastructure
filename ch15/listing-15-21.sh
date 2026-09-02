# Listing 15-21. A development build with assertions enabled
# Run: bash listing-15-21.sh

# # Always build with assertions for development
cmake -DLLVM_ENABLE_ASSERTIONS=ON

# # Use sanitizers during development
clang++ -fsanitize=address,undefined -g source.cpp

# # Profile memory usage when needed
# valgrind --tool=massif ./program
