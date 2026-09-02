# Listing 12-50. Running the backend and reading the assembly
# Run: bash listing-12-50.sh

llc -march=myarch test_add.ll -o -
