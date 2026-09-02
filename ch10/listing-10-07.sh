# Listing 10-7. Running the pass with opt
# Run: bash listing-10-07.sh

opt -load-pass-plugin ./libLoopSideEffectPass.so \
    -passes='function(loop-effect-printer)' \
    -disable-output \
    test.ll
