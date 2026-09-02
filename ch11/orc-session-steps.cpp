// orc-session-steps.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only orc-session-steps.cpp

// orc-session-steps.cpp
//
// The ORC set-up the chapter walks through one statement at a time: the
// ExecutionSession that owns everything, the JITDylib symbols resolve in, a
// self-hosted ExecutorProcessControl, a multi-symbol lookup, turning a looked-up
// address into a callable pointer, and building a lazy JIT. Each is printed as a line
// or two with nothing in scope.
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/SelfExecutorProcessControl.h"
#include "llvm/Support/Error.h"

#include <memory>

using namespace llvm;
using namespace llvm::orc;

// An ExecutionSession needs an ExecutorProcessControl: it has to know what it is
// executing into before it can own anything. The chapter prints
// `std::make_unique<ExecutionSession>()` with no argument, which has not been a valid
// construction since the EPC became mandatory.
std::unique_ptr<ExecutionSession> make_session() {
  auto EPC = cantFail(orc::SelfExecutorProcessControl::Create());
  auto ES = std::make_unique<orc::ExecutionSession>(std::move(EPC));
  return ES;
}

void create_dylib(std::unique_ptr<ExecutionSession> &ES) {
  // createJITDylib returns Expected<JITDylib &> (Core.h:1455), not JITDylib &. The
  // chapter writes `auto &JD = ES->createJITDylib("main");`, which cannot bind a
  // non-const reference to the temporary Expected; the value has to be unwrapped.
  auto &JD = cantFail(ES->createJITDylib("main"));
  (void)JD;
}

void lookup_several(ExecutionSession &ES, JITDylib &JD) {
  // The chapter builds a SymbolNameSet and passes it to lookup. There is no such
  // overload: lookup takes a SymbolLookupSet (Core.h:1536), which carries a required/
  // weak flag per symbol as well as the name. SymbolNameSet still exists, so this
  // fails at overload resolution rather than on the declaration, which is why it
  // reads as correct.
  SymbolLookupSet Names;
  Names.add(ES.intern("foo_init"));
  Names.add(ES.intern("foo_run"));
  Names.add(ES.intern("foo_cleanup"));

  cantFail(ES.lookup(makeJITDylibSearchOrder({&JD}), Names));
}

int call_looked_up(ExecutorSymbolDef Sym) {
  auto *MainFn = Sym.toPtr<int (*)()>();

  int Result = MainFn();  // triggers compilation of 'main'
  return Result;
}

std::unique_ptr<LLLazyJIT> make_lazy_jit() {
  auto JIT = ExitOnError()(LLLazyJITBuilder().create());
  return JIT;
}
