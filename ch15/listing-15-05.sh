# Listing 15-5. Running the test suite with lit
# Run: bash listing-15-05.sh

# # Run all LLVM tests
lit -v llvm/test/

# # Run specific directory with 8 parallel jobs
lit -j8 llvm/test/Transforms/

# # Run single test file
lit llvm/test/Analysis/BasicAA/phi-values.ll

# # Generate JSON report
lit -o results.json llvm/test/
