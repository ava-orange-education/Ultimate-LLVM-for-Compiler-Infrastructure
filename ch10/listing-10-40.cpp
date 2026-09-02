// Listing 10-40. Repairing SSA after the hoist

void updateSSA(Value *OldVal, Value *HoistedVal, BasicBlock *Preheader) {
  SSAUpdater SSA;
  SSA.Initialize(OldVal->getType(), "b.ssa");
  SSA.AddAvailableValue(Preheader, HoistedVal);

  // RewriteUse handles a use in the middle of a block, and a phi use, which
  // takes its value in the predecessor rather than in the phi's own block.
  // make_early_inc_range because setting a use unlinks it from the list
  // being walked.
  for (Use &U : make_early_inc_range(OldVal->uses()))
    SSA.RewriteUse(U);
}
