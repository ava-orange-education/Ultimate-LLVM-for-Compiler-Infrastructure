// Listing 11-28. Optimizing each module on its way to the compiler
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-28.cpp

#include "llvm/ExecutionEngine/Orc/IRTransformLayer.h"
#include "llvm/ExecutionEngine/Orc/Layer.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/Error.h"

using namespace llvm;
using namespace llvm::orc;

// An optimising transform, run on each module on its way to the compile layer.
// The legacy FunctionPassManager and createInstructionCombiningPass() this was
// written against are gone: the legacy pass manager was removed from the
// optimisation pipeline, and passes are now built through PassBuilder.
//
// The MaterializationResponsibility parameter is a non-const reference -- the
// transform may need to modify it -- so a callable taking it by const reference
// does not match IRTransformLayer::TransformFunction and will not bind.
Expected<ThreadSafeModule> optimizeModule(ThreadSafeModule TSM,
                                          MaterializationResponsibility &R) {
  // withModuleDo takes the context lock for the duration, so the module can be
  // touched safely even while other modules compile on other threads.
  TSM.withModuleDo([](Module &M) {
    PassBuilder PB;

    LoopAnalysisManager LAM;
    FunctionAnalysisManager FAM;
    CGSCCAnalysisManager CGAM;
    ModuleAnalysisManager MAM;
    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

    FunctionPassManager FPM = PB.buildFunctionSimplificationPipeline(
        OptimizationLevel::O2, ThinOrFullLTOPhase::None);

    for (Function &F : M)
      if (!F.isDeclaration())
        FPM.run(F, FAM);
  });

  return std::move(TSM);
}

// optimizeModule becomes the transform here, not just by having the right
// signature -- it has to be passed into IRTransformLayer to actually run.
IRTransformLayer makeOptLayer(ExecutionSession &ES, IRLayer &BaseLayer) {
  return IRTransformLayer(ES, BaseLayer, optimizeModule);
}
