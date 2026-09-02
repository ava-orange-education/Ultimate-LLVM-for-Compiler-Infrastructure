// Listing 8-16. A copy GVN propagates away
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-16.cpp

int bar() {
    int x = 10;
    int y = x;   // A trivial copy.
    int z = y + 5;
    int w = 10 + 5;  // Constant expression
    return z + w;
}
