// MyPPCallbacks.h
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PPCallbacks.h"

class MyPPCallbacks : public clang::PPCallbacks {
    public:
        MyPPCallbacks(clang::SourceManager &SM) : SM(SM) {}
        void MacroExpands(const clang::Token &MacroNameTok, const clang::MacroDefinition &MD, clang::SourceRange Range, const clang::MacroArgs *Args) override {
            clang::SourceLocation Loc = Range.getBegin();
            clang::PresumedLoc PLoc = SM.getPresumedLoc(Loc);
            if (PLoc.isValid()) {
                llvm::StringRef FileName = PLoc.getFilename();
                if (SM.isInMainFile(Loc)) {
                    llvm::errs() << "Macro expanded: " << MacroNameTok.getIdentifierInfo()->getName() << "\n";
                }
            }
        }
        void MacroDefined(const clang::Token &MacroNameTok,
            const clang::MacroDirective *MD) override {
            clang::SourceLocation Loc = MacroNameTok.getLocation();
            clang::PresumedLoc PLoc = SM.getPresumedLoc(Loc);
            if (PLoc.isValid()) {
                llvm::StringRef FileName = PLoc.getFilename();
                if (SM.isWrittenInMainFile(Loc)) {
                    llvm::errs() << "Macro defined: " << MacroNameTok.getIdentifierInfo()->getName() << "\n";
                }
            }
        }
        clang::SourceManager &SM;
        // You can override other methods as needed.
};
