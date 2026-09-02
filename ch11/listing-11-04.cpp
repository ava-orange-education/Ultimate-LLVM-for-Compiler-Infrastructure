// Listing 11-4. Interpreting a module from your own tool
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-04.cpp

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <memory>
#include <string>

using namespace llvm;

int interpret(std::unique_ptr<Module> M) {
  std::string ErrStr;

  // EngineBuilder takes ownership of the module. Asking for the Interpreter
  // kind skips code generation entirely and walks the IR instead.
  ExecutionEngine *EE = EngineBuilder(std::move(M))
                            .setEngineKind(EngineKind::Interpreter)
                            .setErrorStr(&ErrStr)
                            .create();
  if (!EE)
    return 1;

  Function *MainFn = EE->FindFunctionNamed("main");
  if (!MainFn)
    return 1;

  GenericValue Result = EE->runFunction(MainFn, {});
  return (int)Result.IntVal.getSExtValue();
}
