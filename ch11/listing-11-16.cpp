// Listing 11-16. A compiler of your own in the compile layer
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-16.cpp

#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/MemoryBuffer.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

// IRCompiler is nested inside IRCompileLayer, so it is named
// IRCompileLayer::IRCompiler. The call operator hands back the compiled object
// as a memory buffer: the compile layer's job is IR in, object bytes out.
class MyCompiler : public IRCompileLayer::IRCompiler {
public:
  // The base class has no default constructor -- it needs the mangling options
  // the layer will use when it maps symbol names.
  MyCompiler() : IRCompiler(IRSymbolMapper::ManglingOptions()) {}

  Expected<std::unique_ptr<MemoryBuffer>> operator()(Module &M) override {
    // Inspect or modify the IR here, before code generation, then emit the
    // object. Returning an Error reports the failure through the JIT.
    return make_error<StringError>("MyCompiler: not implemented",
                                   inconvertibleErrorCode());
  }
};
