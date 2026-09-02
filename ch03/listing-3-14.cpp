// Listing 3-14. Setting up an AST matcher
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-3-14.cpp

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

class FunctionPrinter : public MatchFinder::MatchCallback {
public:
    void run(const MatchFinder::MatchResult &Result) override {
        if (const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
            llvm::outs() << "Function name: " << FD->getNameInfo().getName().getAsString() << "\n";
        }
    }
};

int main(int argc, const char **argv) {
    // CommonOptionsParser cannot be constructed directly -- the constructor is
    // protected because parsing can fail. create() returns an Expected instead.
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    CommonOptionsParser &OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    FunctionPrinter Printer;
    MatchFinder Finder;
    Finder.addMatcher(functionDecl().bind("functionDecl"), &Printer);
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
