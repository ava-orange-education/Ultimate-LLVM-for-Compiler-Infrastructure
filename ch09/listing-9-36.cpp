// Listing 9-36. The same partial redundancy in a whole function
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-9-36.cpp

int compute(int a, int b, int cond) {
    int t;
    if (cond) {
        t = a + b;
        // ... some computations using t ...
    }
    // Later, a+b is used regardless of cond:
    int result = (cond ? t : a + b) * 2;
    return result;
}
