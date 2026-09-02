// Listing 10-56. Re-querying it instead

auto &LI = FAM.getResult<LoopAnalysis>(F);
// ... mutation happens ...
// getResult runs the analysis only on a cache miss, so asking again hands back
// the same stale LoopInfo. Drop the cached result first.
PreservedAnalyses PA;
PA.abandon<LoopAnalysis>();
FAM.invalidate(F, PA);
auto &NewLI = FAM.getResult<LoopAnalysis>(F);
