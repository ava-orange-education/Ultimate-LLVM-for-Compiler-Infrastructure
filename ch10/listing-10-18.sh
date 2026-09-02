# Listing 10-18. How the pipeline is parsed into units
# Run: bash listing-10-18.sh

opt -passes="function(instcombine, loop(my-loop-pass))"
