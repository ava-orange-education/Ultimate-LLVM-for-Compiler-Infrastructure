# Listing 10-19. Two function pipelines: two traversals
# Run: bash listing-10-19.sh

opt -passes="function(instcombine), function(dce)"
