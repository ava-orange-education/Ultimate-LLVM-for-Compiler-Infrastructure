// Listing 11-21. Two lookups compiling at the same time
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-21.cpp

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Error.h"
#include <memory>
#include <thread>

using namespace llvm;
using namespace llvm::orc;

// Two lookups from two threads. Because the JIT was built with a concurrent
// compiler and a thread-safe context, foo and bar can compile at the same time.
void runConcurrently(std::unique_ptr<Module> M, std::unique_ptr<LLVMContext> Ctx) {
  auto JIT = cantFail(LLLazyJITBuilder().create());
  cantFail(JIT->addLazyIRModule(ThreadSafeModule(std::move(M), std::move(Ctx))));

  std::thread T1([&] {
    auto F = cantFail(JIT->lookup("foo"));
    F.toPtr<void (*)()>()();
  });
  std::thread T2([&] {
    auto G = cantFail(JIT->lookup("bar"));
    G.toPtr<void (*)()>()();
  });

  T1.join();
  T2.join();
}
