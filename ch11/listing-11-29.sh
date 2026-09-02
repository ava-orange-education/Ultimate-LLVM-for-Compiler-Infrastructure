# Listing 11-29. Instrumenting a module to collect a profile
# Run: bash listing-11-29.sh

opt -passes=pgo-instr-gen,instrprof input.ll -o instrumented.ll
