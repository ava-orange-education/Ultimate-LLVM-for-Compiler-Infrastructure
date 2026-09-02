// Listing 6-46. Creating the context and the module
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-6-46.cpp

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
llvm::LLVMContext Context;
llvm::Module *Module = new llvm::Module("my_module", Context);
llvm::IRBuilder<> Builder(Context);
