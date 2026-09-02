// Listing 4-3. Wiring the action into main with CommonOptionsParser
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-4-03.cpp

// main.cpp
#include "clang/Tooling/ArgumentsAdjusters.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "SyntaxCheckAction.h"

static llvm::cl::OptionCategory MyToolCategory("custom-clang-tool options");
static llvm::cl::opt<std::string>
    Desc("desc",
            llvm::cl::desc("This is the custom clang tool developed by AVA"),
            llvm::cl::cat(MyToolCategory));
int main(int argc, const char **argv) {
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, MyToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    clang::tooling::CommonOptionsParser &OptionsParser = ExpectedParser.get();
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
                                   OptionsParser.getSourcePathList());
    Tool.clearArgumentsAdjusters();
    Tool.appendArgumentsAdjuster(clang::tooling::getClangStripOutputAdjuster());
    Tool.appendArgumentsAdjuster(clang::tooling::getClangStripDependencyFileAdjuster());
    return Tool.run(clang::tooling::newFrontendActionFactory<SyntaxCheckAction>().get());
}
