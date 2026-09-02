// Listing 8-14. Two additions GVN can prove equal
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-14.cpp

int foo(int a, int b) {
    int sum1 = a + b;
    int sum2 = b + a;  // Commutative: same as a + b.
    int result = sum1 * 2 + sum2; // Redundant: both sum1 and sum2 hold the same value.
    return result;
}
