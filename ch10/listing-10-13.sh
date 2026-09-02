# Listing 10-13. Running the marker pass
# Run: bash listing-10-13.sh

opt -load-pass-plugin ./libLoopSideEffect.so -passes='loop-effect-marker'  ../test.ll --debug-pass-manager -S
