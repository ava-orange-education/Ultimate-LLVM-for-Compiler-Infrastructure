// Listing 4-16. Splitting a location into a FileID and an offset

std::pair<FileID, unsigned> DecomposedLoc = SourceMgr.getDecomposedLoc(SomeLoc);

FileID FID = DecomposedLoc.first;
unsigned Offset = DecomposedLoc.second;
