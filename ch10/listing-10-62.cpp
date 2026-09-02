// Listing 10-62. Tearing a dead block down before erasing it

// DeleteDeadBlock drops the block's own references and erases it. Its
// precondition is that no predecessor branches to DeadBB any more: while one
// does, the block is still a used Value and erasing it is a fatal error.
DeleteDeadBlock(DeadBB);
