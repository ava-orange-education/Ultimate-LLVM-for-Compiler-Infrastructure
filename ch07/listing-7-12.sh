# Listing 7-12. Watching the pass manager build its pipeline
# Run: bash listing-7-12.sh

opt -passes='default<O2>' -debug-pass-manager input.bc -o /dev/null
