# Listing 7-11. Turning the debug output on
# Run: bash listing-7-11.sh

# # DEBUG_TYPE is "my-pass" in the listing above, so ask for that channel by name.
# # -debug turns on every channel at once, which is rarely what you want.
opt -passes=my-pass -debug-only=my-pass input.ll -S
