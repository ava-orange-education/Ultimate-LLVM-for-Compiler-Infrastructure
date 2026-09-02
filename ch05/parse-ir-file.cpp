// parse-ir-file.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only parse-ir-file.cpp

// parse-ir-file.cpp
//
// Reading a .ll file into an in-memory Module. The book prints the three declarations
// on their own; a context, a diagnostic sink and the parse call only mean something
// together, and the error path matters -- parseIRFile returns null on failure and the
// SMDiagnostic is the only place the reason is recorded.
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>

int main(int argc, char **argv) {
  llvm::LLVMContext Context;
  llvm::SMDiagnostic Error;
  std::unique_ptr<llvm::Module> Module = llvm::parseIRFile("input.ll", Error, Context);

  if (!Module) {
    Error.print(argv[0], llvm::errs());
    return 1;
  }

  llvm::outs() << "Parsed module: " << Module->getName() << "\n";
  for (const llvm::Function &F : *Module)
    llvm::outs() << "  function: " << F.getName() << "\n";
  return 0;
}
