// Listing 8-7. A comparison that bounds a value
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-07.cpp

int checkValue(int x) {
    if (x < 100) {
        // do something
    } else {
        // do something else
    }
    if (x < 200) {
        // further processing
    }
    return x;
}
