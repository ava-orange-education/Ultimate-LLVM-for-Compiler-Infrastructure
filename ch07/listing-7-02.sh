# Listing 7-2. A module pass in a function pipeline is rejected
# Run: bash listing-7-02.sh

opt -passes='no-op-function,no-op-module' input.ll -S
# opt: unknown function pass 'no-op-module'
