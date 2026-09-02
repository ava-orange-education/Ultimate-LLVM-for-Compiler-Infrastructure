# Listing 15-8. Building with MemorySanitizer
# Run: bash listing-15-08.sh

# # Compile with MSan
clang -fsanitize=memory -g program.c

# # With origin tracking
clang -fsanitize=memory -fsanitize-memory-track-origins program.c
