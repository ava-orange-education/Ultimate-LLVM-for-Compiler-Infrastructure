// Listing 11-18. Building a module under a thread-safe context
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-18.cpp

#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

ThreadSafeModule makeModule() {
  // ThreadSafeContext owns the LLVMContext and hands it out only inside a
  // callback, which is what makes it safe to share between compile threads.
  // There is no getContext() accessor -- the context is never simply borrowed.
  ThreadSafeContext TSCtx(std::make_unique<LLVMContext>());

  auto M = TSCtx.withContextDo([](LLVMContext *Ctx) {
    return std::make_unique<Module>("concurrent", *Ctx);
  });

  // The module and the context that owns it are moved into the same wrapper.
  return ThreadSafeModule(std::move(M), std::move(TSCtx));
}

std::unique_ptr<ConcurrentIRCompiler> makeCompiler() {
  auto JTMB = cantFail(JITTargetMachineBuilder::detectHost());
  // JITTargetMachineBuilder is move-only, so it is moved in, not copied.
  return std::make_unique<ConcurrentIRCompiler>(std::move(JTMB));
}
