// Listing 3-11. A translation unit with two functions
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-3-11.cpp

int add(int a, int b) {
    return a + b;
}
int main() {
    int result = add(5, 3);
    return 0;
}
