// Listing 3-24. Registering a frontend action as a plugin

...
...

// rest of setup code
...
class MyASTAction : public PluginASTAction {
protected:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) override {
        return std::make_unique<MyASTConsumer>();
    }
    bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string> &args) override {
        return true;
    }
};
static FrontendPluginRegistry::Add<MyASTAction> X("my-ast-action", "My AST Action");
