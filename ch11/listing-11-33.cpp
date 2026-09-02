// Listing 11-33. Step 3: adding the module with its own context
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-33.cpp

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Error.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

int buildAndRun(LLJIT &JIT) {
  ExitOnError ExitOnErr;

  // The context has to be heap-allocated and handed to the ThreadSafeModule
  // along with the module built from it. A module belongs to exactly one
  // context: pairing it with a freshly made second context is not valid.
  auto Ctx = std::make_unique<LLVMContext>();
  auto Mod = std::make_unique<Module>("test_module", *Ctx);

  ExitOnErr(JIT.addIRModule(ThreadSafeModule(std::move(Mod), std::move(Ctx))));

  ExecutorAddr Sym = ExitOnErr(JIT.lookup("foo"));
  auto *FooFn = Sym.toPtr<int (*)()>();
  return FooFn();
}
