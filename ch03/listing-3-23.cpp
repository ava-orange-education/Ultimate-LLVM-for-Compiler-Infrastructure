// Listing 3-23. The skeleton of a LibTooling tool
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-3-23.cpp

#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang::tooling;

static llvm::cl::OptionCategory ToolCategory("my-tool options");

class MyFrontendAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &CI, llvm::StringRef InFile) override {
        // Custom ASTConsumer implementation
        return std::make_unique<clang::ASTConsumer>();
    }
};

int main(int argc, const char **argv) {
    // CommonOptionsParser has had a protected constructor since LLVM 10: it can
    // fail, so it is built through create(), which hands back an Expected.
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, ToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    CommonOptionsParser &OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());
    return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
