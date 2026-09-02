# Listing 15-2. Running a FileCheck test over llc output
# Run: bash listing-15-02.sh

# # Run the test
llc test.ll -o - | FileCheck test.ll
