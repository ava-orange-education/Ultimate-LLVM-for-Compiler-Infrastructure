// Listing 11-17. Generating definitions for symbols nothing defines
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-17.cpp

#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/Support/Error.h"

using namespace llvm;
using namespace llvm::orc;

// A generator is consulted when a lookup finds nothing. It can define the
// missing symbols on the spot -- compiling a script function on first use, say.
class ScriptFunctionGenerator : public DefinitionGenerator {
public:
  Error tryToGenerate(LookupState &LS, LookupKind K, JITDylib &JD,
                      JITDylibLookupFlags JDLookupFlags,
                      const SymbolLookupSet &LookupSet) override {
    // Build the definitions for anything in LookupSet, then hand them over with
    // JD.define(...). Returning success without defining anything simply means
    // the symbols stay unresolved.
    return Error::success();
  }
};
