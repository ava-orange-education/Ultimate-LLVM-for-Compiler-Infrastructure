// Listing 4-6. Finding C-style casts with a RecursiveASTVisitor
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-4-06.cpp

// MyASTConsumer.h
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
    public:
        explicit MyASTVisitor(clang::ASTContext *Context) : Context(Context) {}
        bool VisitCStyleCastExpr(clang::CStyleCastExpr *Cast) {
            clang::SourceManager &SM = Context->getSourceManager();
            clang::SourceLocation Loc = Cast->getExprLoc();
            std::string Filename = SM.getFilename(Loc).str();
            unsigned Line = SM.getSpellingLineNumber(Loc);
            unsigned Column = SM.getSpellingColumnNumber(Loc);
            if (SM.isWrittenInMainFile(Loc)) {
                llvm::outs() << "Found C-style cast at " << Filename << ":" << Line << ":" << Column << "\n";
            }
            return true;
        }
    private:
        clang::ASTContext *Context;
};

class MyASTConsumer : public clang::ASTConsumer {
    public:
        explicit MyASTConsumer(clang::ASTContext *Context) : Visitor(Context) {}
        void HandleTranslationUnit(clang::ASTContext &Context) override {
            Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        }
    private:
        MyASTVisitor Visitor;
};
