# Listing 15-29. Combining optimisation flags
# Run: bash listing-15-29.sh

# Use optimization flags strategically
clang -O3 -ffast-math -flto -fprofile-instr-use=profile.profdata

# Combine multiple optimization approaches
# LTO + PGO can yield 10-20% additional performance
