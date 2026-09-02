# Listing 7-3. Wrapping it in an adapter so the pipeline nests
# Run: bash listing-7-03.sh

opt -passes='function(no-op-function),no-op-module' input.ll -S

# Here, the function(no-op-function), creates a Module adapter pass and runs no-op-function on each function with a module
