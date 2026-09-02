// Listing 9-30. A tail-recursive factorial
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-9-30.cpp

int factorial_tail(int n, int acc) {
    if (n == 0)
        return acc;
    else
        return factorial_tail(n - 1, n * acc);
}

int factorial(int n) {
    return factorial_tail(n, 1);
}
