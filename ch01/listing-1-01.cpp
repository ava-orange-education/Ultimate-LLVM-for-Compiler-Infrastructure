// Listing 1-1. A C program with an out-of-bounds array access
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-1-01.cpp

// example.c
#include <stdio.h>
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("Element at index 10 is %d\n", arr[10]); // Out-of-bounds access
    return 0;
}
