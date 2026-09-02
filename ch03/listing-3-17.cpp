// Listing 3-17. Code with an uninitialised variable
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-3-17.cpp

int main() {
    int x = 0;
    int y; // Warning: variable 'y' is uninitialized
    return x + y;   // y is read here, which is what -Wuninitialized reports

}
