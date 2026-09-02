// Listing 10-14. What opt prints as the passes run

Running analysis: InnerAnalysisManagerProxy<llvm::AnalysisManager<llvm::Function>, llvm::Module> on [module]
Running pass: LoopEffectMarkerPass on checkContext (24 instructions)
Running analysis: LoopSideEffectAnalysis on checkContext
...
Running analysis: OuterAnalysisManagerProxy<llvm::AnalysisManager<llvm::Module>, llvm::Function> on checkContext
Loop in function checkContext:
  - Writes to memory
