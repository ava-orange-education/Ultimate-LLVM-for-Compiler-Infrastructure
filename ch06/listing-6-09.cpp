// Listing 6-9. Pointer dereferencing in C
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-6-09.cpp

// C Code Example
void example() {
    int x = 42;
    int *ptr = &x;  // Referencing
    *ptr = 10;      // Dereferencing
}
