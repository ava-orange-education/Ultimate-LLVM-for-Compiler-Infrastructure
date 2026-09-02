// Listing 8-5. An induction variable the analysis can bound
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-05.cpp

int accumulate(int *result, int n, int k) {
    int t = 0;
    for (int i = 0; i < n; i++) {
        t = t + k;
    }
    *result = t;
    return t;
}
