# Listing 15-17. Formatting a file, and checking it stays formatted
# Run: bash listing-15-17.sh

# # Format a file in place, using the nearest .clang-format
clang-format -i mysource.cpp

# # Check formatting without changing the file; fails if it is not already clean
clang-format --dry-run -Werror mysource.cpp
