// Listing 10-6. Registering both passes as a plugin

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "LoopEffectMarkerPass", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "loop-effect-printer") {
            FPM.addPass(LoopSideEffectAnalysisPrinterPass());
            return true;
          }
          return false;
        });
      PB.registerAnalysisRegistrationCallback(
        [](FunctionAnalysisManager &FAM) {
          FAM.registerPass([] { return LoopSideEffectAnalysis(); });
        });
    	PB.registerPipelineStartEPCallback([](ModulePassManager &MPM,
          OptimizationLevel Level) {
        FunctionPassManager FPM;
        FPM.addPass(LoopSideEffectAnalysisPrinterPass());
        MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
        });
    }
  };
}
