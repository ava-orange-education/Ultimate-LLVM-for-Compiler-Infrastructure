# Listing 15-9. Building with ThreadSanitizer
# Run: bash listing-15-09.sh

# # Compile with TSan
clang -fsanitize=thread -g program.c
