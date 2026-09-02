# Listing 15-1. Why FileCheck rather than diff
# Run: bash listing-15-01.sh

# # diff is too strict - fails on small differences
diff expected.txt actual.txt

# # FileCheck is flexible - checks patterns that matter
FileCheck expected.txt < actual.txt
