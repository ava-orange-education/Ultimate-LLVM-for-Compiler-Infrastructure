// custom-memory-manager.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only custom-memory-manager.cpp

#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"

using namespace llvm;
using namespace llvm::orc;

// A memory manager of your own: the factory is called once per object, and is handed
// the object buffer, so the choice can vary from one object to the next.
class MyCustomMemoryManager : public SectionMemoryManager {};

RTDyldObjectLinkingLayer makeObjectLayer(ExecutionSession &ES) {
  return RTDyldObjectLinkingLayer(ES, [](const MemoryBuffer &) {
    return std::make_unique<MyCustomMemoryManager>();
  });
}
