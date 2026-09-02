// Listing 5-3. Writing a module out as text or as bitcode
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-5-03.cpp

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

void dumpModule(llvm::Module *Module) {
  // For textual IR:
  Module->print(llvm::outs(), nullptr);
  // For Bitcode IR:
  llvm::WriteBitcodeToFile(*Module, llvm::outs());
}
