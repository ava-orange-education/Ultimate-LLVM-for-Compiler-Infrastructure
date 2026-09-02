// Listing 3-7. An include for the preprocessor to resolve
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-3-07.cpp

// main.cpp -- header.h sits beside it; see the repo files for this chapter.
#include "header.h"
int main() { return 0; }
