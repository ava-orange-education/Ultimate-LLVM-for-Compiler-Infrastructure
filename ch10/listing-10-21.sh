# Listing 10-21. The same nesting, revisited as a repeated-traversal pitfall
# Run: bash listing-10-21.sh

opt -passes="function(loop(loop-side-effect-tag), dce)"
