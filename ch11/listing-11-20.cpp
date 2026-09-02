// Listing 11-20. Fixing the threading policy when the session is built
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-20.cpp

#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/SelfExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/TaskDispatch.h"
#include "llvm/Support/Error.h"
#include <memory>
#include <optional>

using namespace llvm;
using namespace llvm::orc;

// The threading policy is chosen when the session is built, not changed on a
// live session: there is no ExecutionSession::setDispatchTask. A TaskDispatcher
// is handed to the ExecutorProcessControl, and the session takes it from there.
//
//   InPlaceTaskDispatcher              runs every task on the calling thread
//   DynamicThreadPoolTaskDispatcher    spawns threads, optionally capped
Expected<std::unique_ptr<ExecutionSession>> makeSession(size_t MaxThreads) {
  auto EPC = SelfExecutorProcessControl::Create(
      /*SSP=*/nullptr,
      std::make_unique<DynamicThreadPoolTaskDispatcher>(MaxThreads));
  if (!EPC)
    return EPC.takeError();

  return std::make_unique<ExecutionSession>(std::move(*EPC));
}
