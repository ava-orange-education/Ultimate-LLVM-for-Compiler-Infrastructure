// Listing 4-2. Setting up a syntax-only FrontendAction
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-4-02.cpp

// main.cpp
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::tooling;

class SyntaxCheckAction : public clang::ASTFrontendAction {

public:
    SyntaxCheckAction() = default;

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &CI,
        llvm::StringRef InFile) override {
        // Return a default ASTConsumer
        return std::make_unique<ASTConsumer>();
    }

    bool BeginInvocation(CompilerInstance &CI) override { return true; }

    virtual bool BeginSourceFileAction(CompilerInstance &CI) override {
        llvm::outs() << "Starting source file action on: " << getCurrentFile() << "\n";
        return true;
    }

    void EndSourceFileAction() override {

        llvm::outs() << "Syntax check completed.\n";
    }
};
