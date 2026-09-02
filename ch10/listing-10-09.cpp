// Listing 10-9. Using the analysis result in run()

PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    auto &LoopEffects = FAM.getResult<LoopSideEffectAnalysis>(F);
    LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);

    for (Loop *L : LI.getLoopsInPreorder()) {

      auto InfoIt = LoopEffects.find(L);
      if (InfoIt == LoopEffects.end()) continue;

      const LoopSideEffectInfo &Info = InfoIt->second;
      errs() << "Loop in function " << F.getName() << ":\n";
      if (Info.hasMemoryWrite) errs() << "  - Writes to memory\n";
      if (Info.hasVolatileAccess) errs() << "  - Has volatile access\n";
      if (Info.hasFunctionCallWithSideEffects) errs() << "  - Calls with side effects\n";

      if (Info.hasMemoryWrite || Info.hasFunctionCallWithSideEffects) {
        BasicBlock *Header = L->getHeader();
        if (BranchInst *BI = dyn_cast<BranchInst>(Header->getTerminator())) {
          attachLoopMetadata(BI, BI->getContext());
        }
      }
    }
    return PreservedAnalyses::all();
  }
