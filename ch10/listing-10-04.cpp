// Listing 10-4. The run method of the loop side-effect analysis

LoopSideEffectAnalysis::Result
LoopSideEffectAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  Result SideEffects;
  LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);
  AAResults &AA = FAM.getResult<AAManager>(F);

  // getLoopsInPreorder walks the whole nest. Iterating LoopInfo directly visits only
  // top-level loops, so an inner loop's stores would be attributed to its outermost
  // parent and the inner loop would never get an entry of its own.
  for (Loop *L : LI.getLoopsInPreorder()) {

    LoopSideEffectInfo Info;
    for (BasicBlock *BB : L->blocks()) {
      for (Instruction &I : *BB) {
        // Three independent properties, so three independent ifs. As an else-if
        // chain a `store volatile` matched the first arm only and never set
        // hasVolatileAccess.
        if (isa<StoreInst>(&I)) {

          Info.hasMemoryWrite = true;
        }
        if (I.mayReadOrWriteMemory() && I.isVolatile()) {

          Info.hasVolatileAccess = true;
        }
        if (auto *CI = dyn_cast<CallBase>(&I)) {

          auto ME = AA.getMemoryEffects(CI);
          if (!ME.doesNotAccessMemory()) {
            Info.hasFunctionCallWithSideEffects = true;
          }
        }
      }
    }

    SideEffects[L] = Info;
  }
  return SideEffects;
}
AnalysisKey LoopSideEffectAnalysis::Key;
