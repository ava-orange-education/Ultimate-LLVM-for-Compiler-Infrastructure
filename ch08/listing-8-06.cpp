// Listing 8-6. An affine access pattern
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-06.cpp

void fillArray(int *a, int n, int k) {
    for (int i = 0; i < n; i++) {
        a[i] = i * k;
    }
}
