// Listing 11-12. LLLazyJIT, compiling a function on its first call
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-12.cpp

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Error.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

int runLazily(std::unique_ptr<Module> M, std::unique_ptr<LLVMContext> Ctx) {
  // LLLazyJIT compiles a function the first time it is called rather than when
  // the module is added. Everything else is the same as LLJIT.
  auto JIT = cantFail(LLLazyJITBuilder().create());

  cantFail(JIT->addLazyIRModule(ThreadSafeModule(std::move(M), std::move(Ctx))));

  // The lookup resolves to a stub; no code has been generated yet.
  auto Sym = cantFail(JIT->lookup("main"));

  // Calling through the stub is what triggers compilation.
  auto *MainFn = Sym.toPtr<int (*)()>();
  return MainFn();
}
