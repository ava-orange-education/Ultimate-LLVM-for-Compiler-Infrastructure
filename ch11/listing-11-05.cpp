// Listing 11-5. The shortest LLJIT that compiles and runs a module
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-05.cpp

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Error.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

int runMain(std::unique_ptr<Module> M, std::unique_ptr<LLVMContext> Ctx) {
  // create() hands back Expected<std::unique_ptr<LLJIT>>; cantFail unwraps it
  // and aborts on error. A real tool would inspect the Error instead.
  auto JIT = cantFail(LLJITBuilder().create());

  // The module and the context that owns it travel together.
  cantFail(JIT->addIRModule(ThreadSafeModule(std::move(M), std::move(Ctx))));

  // lookup() returns an ExecutorAddr, which is deliberately not a pointer: the
  // code may live in another process. toPtr gives a callable pointer when it
  // does not.
  auto Sym = cantFail(JIT->lookup("main"));
  auto *MainFn = Sym.toPtr<int (*)()>();
  return MainFn();
}
