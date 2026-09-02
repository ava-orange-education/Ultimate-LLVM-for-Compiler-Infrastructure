// Listing 11-11. LLJIT compiling eagerly, with the module wrapper named
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-11.cpp

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Error.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

int runMainEagerly(std::unique_ptr<Module> M) {
  auto JIT = cantFail(LLJITBuilder().create());

  // Built as a named local rather than inline: a ThreadSafeModule owns both the
  // module and the context, and creating the context here makes that ownership
  // visible. It is what allows the module to be handed to a compile thread.
  ThreadSafeModule TSM(std::move(M), std::make_unique<LLVMContext>());
  cantFail(JIT->addIRModule(std::move(TSM)));

  // LLJIT compiles eagerly: by the time addIRModule returns, the work is queued,
  // and the lookup below resolves an address rather than triggering compilation.
  auto MainSym = cantFail(JIT->lookup("main"));

  // getAddress() yields an ExecutorAddr, not a pointer -- the code may run in
  // another process. toPtr converts it when it does not.
  auto *MainFn = MainSym.toPtr<int (*)()>();
  return MainFn();
}
