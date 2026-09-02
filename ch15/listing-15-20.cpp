// Listing 15-20. StringRef: a string passed without copying

// No copies, just pointer + length
StringRef processName(StringRef FuncName) {  // Pass by value!
  if (FuncName.starts_with("llvm."))
    return FuncName.drop_front(5);
  return FuncName;
}

// Efficient string operations
bool isIntrinsic = FuncName.starts_with("llvm.");
auto Parts = FuncName.split('.');
StringRef Trimmed = FuncName.trim();

// Conversion when needed
std::string Materialized = Name.str(); // Only when storing
