// SyntaxCheckAction.h -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only SyntaxCheckAction.h

// SyntaxCheckAction.h
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "MyPPCallbacks.h"
#include "MyRewriteASTConsumer.h"

class SyntaxCheckAction : public clang::ASTFrontendAction {

public:
    SyntaxCheckAction() = default;
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &CI,
        llvm::StringRef InFile) override {
        TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
        // Return a default ASTConsumer
        return std::make_unique<MyASTConsumer>(&CI.getASTContext(), TheRewriter);
    }

    bool BeginInvocation(CompilerInstance &CI) override {

        llvm::outs() << "Starting custom clang tool invocation: " << getCurrentFile() << "\n";
        return true;
    }

    bool BeginSourceFileAction(CompilerInstance &CI) override {
        llvm::outs() << "Starting source file action on: " << getCurrentFile() << "\n";
        return true;
    }

    void ExecuteAction() override {

        llvm::outs() << "Starting custom clang tool ExecuteAction: " << getCurrentFile() << "\n";
        clang::Preprocessor &PP = getCompilerInstance().getPreprocessor();
        PP.addPPCallbacks(std::make_unique<MyPPCallbacks>(PP.getSourceManager()));

        clang::ASTFrontendAction::ExecuteAction();
    }

    void EndSourceFileAction() override {
        SourceManager &SM = TheRewriter.getSourceMgr();

        llvm::errs() << "** EndSourceFileAction for: "
                     << SM.getFileEntryForID(SM.getMainFileID())->tryGetRealPathName() << "\n";
        TheRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());

        llvm::outs() << "Syntax check completed.\n";
    }

    Rewriter TheRewriter;
};
