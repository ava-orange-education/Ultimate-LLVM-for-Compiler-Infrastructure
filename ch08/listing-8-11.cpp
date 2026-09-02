// Listing 8-11. A function the call graph reaches
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-8-11.cpp

#include <stdio.h>
void baz() {
    printf("Hello from baz!\n");
}
void bar() {
    baz();
}
void foo() {
    bar();
}
int main() {
    foo();
    return 0;
}
