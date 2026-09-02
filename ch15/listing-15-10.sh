# Listing 15-10. Enabling the UndefinedBehaviorSanitizer checks
# Run: bash listing-15-10.sh

# # Enable all UBSan checks
clang -fsanitize=undefined program.c

# # Specific checks
clang -fsanitize=signed-integer-overflow,null program.c
