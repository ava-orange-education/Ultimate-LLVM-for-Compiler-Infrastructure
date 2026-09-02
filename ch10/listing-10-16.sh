# Listing 10-16. The same nesting, revisited as a repeated-traversal pitfall
# Run: bash listing-10-16.sh

opt -passes="function(loop(loop-side-effect-tag), dce)"
