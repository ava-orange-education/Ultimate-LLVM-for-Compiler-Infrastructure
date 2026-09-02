// Listing 15-28. Checking an instruction for a debug location

// Check for debug location availability
if (DILocation *Loc = I->getDebugLoc()) {
    unsigned Line = Loc->getLine();
    StringRef File = Loc->getFilename();
    bool ImplicitCode = Loc->isImplicitCode();
}
