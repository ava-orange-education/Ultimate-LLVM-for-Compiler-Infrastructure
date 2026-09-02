# Listing 15-15. Merging and inspecting profile data
# Run: bash listing-15-15.sh

# # Merge multiple profile runs
llvm-profdata merge -output=merged.profdata run1.profdata run2.profdata

# # Show profile information
llvm-profdata show -all-functions merged.profdata

# # Weighted merge
llvm-profdata merge -weighted-input=3,run1.profdata \
                    -weighted-input=1,run2.profdata \
                    -output=weighted.profdata
