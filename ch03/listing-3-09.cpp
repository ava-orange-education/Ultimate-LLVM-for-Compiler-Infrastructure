// Listing 3-9. Reading the tokens that follow the pragma
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-3-09.cpp

#include <clang/Lex/Preprocessor.h>
#include <llvm/Support/raw_ostream.h>

class MyPragmaHandler : public clang::PragmaHandler {
public:
    MyPragmaHandler() : PragmaHandler("my_pragma") {}
    void HandlePragma(clang::Preprocessor &PP, clang::PragmaIntroducer Introducer, clang::Token &FirstToken) override {
        llvm::outs() << "Encountered #pragma my_pragma!\n";
        clang::Token Tok;
        // Preprocessor::Lex returns void, so the end of the directive is the loop
        // condition rather than the return value.
        PP.Lex(Tok);
        while (!Tok.is(clang::tok::eod)) {
            llvm::outs() << "Token in pragma: " << Tok.getName() << "\n";
            PP.Lex(Tok);
        }
    }
};

void RegisterCustomPragma(clang::Preprocessor &PP) {
    PP.AddPragmaHandler(new MyPragmaHandler());
}
