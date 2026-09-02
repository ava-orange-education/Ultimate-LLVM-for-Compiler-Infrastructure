# Listing 1-26. Running one analyser checker by name
# Run: bash listing-1-26.sh

clang -Xclang -analyzer-checker=core -analyzer-output=text source.c
