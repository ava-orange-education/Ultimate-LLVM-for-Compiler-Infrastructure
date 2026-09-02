// matcher-main.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only matcher-main.cpp

#include "clang/AST/AST.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

static llvm::cl::OptionCategory MyToolCategory("custom-clang-tool options");

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

int main(int argc, const char **argv) {
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, MyToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    clang::tooling::CommonOptionsParser &OptionsParser = ExpectedParser.get();

    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
                                   OptionsParser.getSourcePathList());

    // This is a matcher callback object

    CastFinder Finder;
    // This is the main object which is responsible for running the matchers on AST.
    // It registers the matcher callback with it and runs them over AST
    MatchFinder Matchers;
    Matchers.addMatcher(cStyleCastExpr().bind("cStyleCast"), &Finder);

    return Tool.run(clang::tooling::newFrontendActionFactory(&Matchers).get());
}
