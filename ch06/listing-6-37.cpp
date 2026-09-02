// Listing 6-37. Nested structs in C
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-6-37.cpp

struct Inner {
    int values[3];  // Array inside the struct
    float y;
};
struct Outer {
    double a;
    struct Inner b;
};
void example(struct Outer *ptr) {
    ptr->b.values[1] = 99;  // Modify the second element in the array inside Inner struct
}
