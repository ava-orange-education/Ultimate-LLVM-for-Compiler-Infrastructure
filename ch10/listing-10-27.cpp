// Listing 10-27. Finding what post-dominates a return

for (BasicBlock &BB : F) {
  if (isa<ReturnInst>(BB.getTerminator())) {
    // CleanupBB post-dominates BB when every path leaving BB reaches it, so whatever
    // BB acquires is certain to be released there. DT.dominates would answer the
    // opposite question: what has already run before BB.
    if (CleanupBB && PDT.dominates(CleanupBB, &BB)) {

      IRBuilder<> Builder(&*BB.getFirstInsertionPt());
      Builder.CreateCall(LogFn);
    }
  }
}
