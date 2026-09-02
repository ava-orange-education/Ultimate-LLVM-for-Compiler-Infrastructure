// Listing 15-7. A heap overflow for AddressSanitizer to catch
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-15-07.cpp

// heap-overflow.cpp
int main() {
    int *array = new int[45];
    array[45] = 1;  // Heap buffer overflow!
    delete[] array;
    return 0;
}
