// Listing 11-25. Pointing an LLJIT at a remote executor
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-25.cpp

#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/SimpleRemoteEPC.h"
#include "llvm/ExecutionEngine/Orc/Shared/SimpleRemoteEPCUtils.h"
#include "llvm/ExecutionEngine/Orc/TaskDispatch.h"
#include "llvm/Support/Error.h"
#include <memory>

using namespace llvm;
using namespace llvm::orc;

// Connect to an executor already listening on the other end of `SockFD`, and
// build an LLJIT that compiles here and runs there.
//
// SimpleRemoteEPCTransport is an abstract base: the concrete transport is
// FDSimpleRemoteEPCTransport, and it speaks over file descriptors rather than a
// host-and-port string. SimpleRemoteEPC::Create constructs both together, which
// is why the transport is a template argument rather than a constructed object.
// Modelled on llvm/examples/OrcV2Examples/LLJITWithRemoteDebugging.
Expected<std::unique_ptr<LLJIT>> makeRemoteJIT(int SockFD) {
  auto EPC = SimpleRemoteEPC::Create<FDSimpleRemoteEPCTransport>(
      std::make_unique<DynamicThreadPoolTaskDispatcher>(std::nullopt),
      SimpleRemoteEPC::Setup(), SockFD);
  if (!EPC)
    return EPC.takeError();

  auto ES = std::make_unique<ExecutionSession>(std::move(*EPC));

  return LLJITBuilder()
      .setExecutionSession(std::move(ES))
      .create();
}
