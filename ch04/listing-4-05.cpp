// Listing 4-5. Installing the preprocessor callbacks in ExecuteAction

// SyntaxCheckAction.h

class SyntaxCheckAction : public clang::ASTFrontendAction {
public:
    SyntaxCheckAction() = default;
// ...
void ExecuteAction() override {
        llvm::outs() << "Starting custom clang tool ExecuteAction: " << getCurrentFile() << "\n";
        clang::Preprocessor &PP = getCompilerInstance().getPreprocessor();
        PP.addPPCallbacks(std::make_unique<MyPPCallbacks>(PP.getSourceManager()));
        clang::ASTFrontendAction::ExecuteAction();
    }
// ...
};
