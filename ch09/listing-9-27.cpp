// Listing 9-27. A local variable in C
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-9-27.cpp

int computeSum(int a, int b) {
    int x;         // Allocated on the stack using alloca in LLVM IR.
    x = a + b;
    return x;
}
