// Listing 8-8. An index range analysis can prove in bounds
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-08.cpp

void processArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
        // Use 'i' for array indexing
        a[i] = a[i] * 2;
    }
}
