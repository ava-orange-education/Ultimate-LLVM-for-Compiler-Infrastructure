// Listing 9-23. A struct the optimiser can split apart
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-9-23.cpp

struct Point {
    int x;
    int y;
};

void foo() {
    struct Point p;      // allocated as a single aggregate.
    p.x = 10;
    p.y = 20;
    int sum = p.x + p.y; // use the fields in computation.
}
