// Listing 4-7. Matching C-style casts with a MatchFinder callback
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-4-07.cpp

// MyASTMatcher.h
#include "clang/AST/AST.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

class CastFinder : public MatchFinder::MatchCallback {

public:
    virtual void run(const MatchFinder::MatchResult &Result) {
        const CStyleCastExpr *Cast = Result.Nodes.getNodeAs<CStyleCastExpr>("cStyleCast");
        SourceManager &SM = *Result.SourceManager;
        if (Cast && Cast->getBeginLoc().isValid()) {
            if(SM.isInMainFile(Cast->getBeginLoc())) {

                llvm::errs() << "Matched C-style cast at "
                            << Cast->getBeginLoc().printToString(*Result.SourceManager) << "\n";
            }
        }
    }
};
