// Listing 10-61. Rewiring a conditional branch safely

// Rewire a conditional branch safely: edit the terminator the block already
// has. BranchInst::Create with a BasicBlock* appends to that block, and the
// block already ends in a terminator, so creating one here leaves two.
auto *BI = cast<BranchInst>(Builder.GetInsertBlock()->getTerminator());
BI->setCondition(Cond);
BI->setSuccessor(0, NewTrueBB);
BI->setSuccessor(1, NewFalseBB);
