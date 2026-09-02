// rewrite-cast.h -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only rewrite-cast.h

// rewrite-cast.h
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"

using namespace clang;

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
    public:
        MyASTVisitor(clang::ASTContext *Context, clang::Rewriter &Rewrite)
            : Context(Context), Rewrite(Rewrite) {}

        bool VisitCStyleCastExpr(clang::CStyleCastExpr *Cast) {

            clang::LangOptions LangOpts;
            clang::SourceManager &SM = Context->getSourceManager();
            SourceLocation StartLoc = Cast->getBeginLoc();
            SourceLocation EndLoc = Cast->getEndLoc();

            clang::SourceLocation Loc = Cast->getExprLoc();
            std::string Filename = SM.getFilename(Loc).str();
            unsigned Line = SM.getSpellingLineNumber(Loc);
            unsigned Column = SM.getSpellingColumnNumber(Loc);
            if (SM.isWrittenInMainFile(Loc)) {

                llvm::outs() << "Found C-style cast at " << Filename << ":" << Line << ":" << Column << "\n";
  	// Determine the appropriate C++ cast
                QualType DestType = Cast->getTypeAsWritten();
                Expr *SubExpr = Cast->getSubExpr();
                QualType SrcType = SubExpr->getType();

                std::string CastType = "static_cast";
                if (DestType->isPointerType() && SrcType->isPointerType()) {
                    if (Cast->getCastKind() == CK_BitCast) {
                        CastType = "reinterpret_cast";

                    } else if (Cast->getCastKind() == CK_NoOp) {
                        CastType = "static_cast";
                    }

                } else if (Cast->getCastKind() == CK_Dynamic) {
                    CastType = "dynamic_cast";

                } else {
                    CastType = "static_cast";
                }

                std::string ReplacementText = (llvm::Twine(CastType) + "<" +
                    Cast->getTypeAsWritten().getAsString() + ">(" +
                    clang::Lexer::getSourceText(clang::CharSourceRange::getTokenRange(
                                        Cast->getSubExpr()->getSourceRange()),
                                        SM, LangOpts) + ")").str();
                Rewrite.ReplaceText(Cast->getSourceRange(), ReplacementText);

                llvm::outs() << "Replaced C-style cast with static_cast at " << Filename << ":" << Line << ":" << Column << "\n";
            }
            return true;
        }

    private:
        clang::ASTContext *Context;
        clang::Rewriter &Rewrite;
};

class MyASTConsumer : public clang::ASTConsumer {
    public:
        MyASTConsumer(clang::ASTContext *Context, clang::Rewriter &Rewrite)
            : Visitor(Context, Rewrite) {}
        void HandleTranslationUnit(clang::ASTContext &Context) override {
            Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        }
    private:
        MyASTVisitor Visitor;
};
