// manual-layers.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only manual-layers.cpp

#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"

using namespace llvm;
using namespace llvm::orc;

// The layers are members of the JIT class, not locals: each one refers to the
// layer beneath it, so they must outlive every module added to them. This is
// the arrangement llvm/examples/Kaleidoscope/include/KaleidoscopeJIT.h uses.
class MyJIT {
  std::unique_ptr<ExecutionSession> ES;
  DataLayout DL;
  MangleAndInterner Mangle;
  RTDyldObjectLinkingLayer ObjectLayer;
  IRCompileLayer CompileLayer;
  JITDylib &MainJD;

public:
  MyJIT(std::unique_ptr<ExecutionSession> ES, JITTargetMachineBuilder JTMB,
        DataLayout DL)
      : ES(std::move(ES)), DL(std::move(DL)), Mangle(*this->ES, this->DL),

        // The object layer takes a factory for the memory manager. The callback
        // is handed the object buffer, so it can vary the manager per object.
        ObjectLayer(*this->ES,
                    [](const MemoryBuffer &) {
                      return std::make_unique<SectionMemoryManager>();
                    }),

        // The compile layer sits on top of the object layer and turns IR into
        // objects. JITTargetMachineBuilder is move-only.
        CompileLayer(*this->ES, ObjectLayer,
                     std::make_unique<ConcurrentIRCompiler>(std::move(JTMB))),

        MainJD(this->ES->createBareJITDylib("<main>")) {

    // Let unresolved symbols fall through to the host process, so the JIT'd
    // code can call printf and friends. GetForCurrentProcess takes the platform's
    // global symbol prefix, not the DataLayout itself.
    MainJD.addGenerator(cantFail(
        DynamicLibrarySearchGenerator::GetForCurrentProcess(
            DL.getGlobalPrefix())));
  }

  Error addModule(ThreadSafeModule TSM) {
    return CompileLayer.add(MainJD.getDefaultResourceTracker(), std::move(TSM));
  }

  Expected<ExecutorSymbolDef> lookup(StringRef Name) {
    return ES->lookup({&MainJD}, Mangle(Name.str()));
  }
};
