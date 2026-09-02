# Listing 10-17. A pipeline string with three passes
# Run: bash listing-10-17.sh

opt -passes="function(instcombine, loop(loop-side-effect-tag), dce)"
