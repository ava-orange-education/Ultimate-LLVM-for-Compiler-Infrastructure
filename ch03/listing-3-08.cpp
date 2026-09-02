// Listing 3-8. A handler for a pragma of your own
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-3-08.cpp

#include <clang/Lex/Preprocessor.h>
#include <llvm/Support/raw_ostream.h>

class MyPragmaHandler : public clang::PragmaHandler {
public:
    MyPragmaHandler() : PragmaHandler("my_pragma") {}
    void HandlePragma(clang::Preprocessor &PP, clang::PragmaIntroducer Introducer, clang::Token &FirstToken) override {
        llvm::outs() << "Custom pragma encountered.\n";
    }
};
