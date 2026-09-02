// Listing 8-15. After GVN: one addition, reused
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-15.cpp

int foo(int a, int b) {
    int sum = a + b;
    int result = sum * 3; // Because sum1 and sum2 are equal.
    return result;
}
