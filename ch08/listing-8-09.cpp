// Listing 8-9. A range propagated through arithmetic
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-09.cpp

int multiplyExample(int x) {
    int y = x * 3;
    if (y < 50)
        return y;
    else
        return 50;
}
