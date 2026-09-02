# Listing 11-30. Recompiling with the collected profile
# Run: bash listing-11-30.sh

opt -passes=pgo-instr-use -pgo-test-profile-file=merged.profdata input.ll -o optimized.ll
