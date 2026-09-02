// Listing 10-49. A builder with no insertion point crashes
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-10-49.cpp

IRBuilder<> B;
Value *V = B.CreateAdd(X, Y); // crash: insert point not set!
