// rewrite-cast-fixit.h -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only rewrite-cast-fixit.h

// rewrite-cast-fixit.h
//
// The variant of the cast rewriter that attaches a FixItHint to the diagnostic
// instead of editing the buffer directly. rewrite-cast-with-note.h calls
// Rewriter::ReplaceText and reports a plain Note; here the replacement travels
// with the diagnostic, so `clang-tool -fix` can apply it and an IDE can offer it.
#ifndef REWRITE_CAST_FIXIT_H
#define REWRITE_CAST_FIXIT_H

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Lexer.h"

using namespace clang;

class FixItCastVisitor : public RecursiveASTVisitor<FixItCastVisitor> {
public:
  explicit FixItCastVisitor(ASTContext *Context) : Context(Context) {}

  bool VisitCStyleCastExpr(CStyleCastExpr *CStyleCast) {
    SourceManager &SM = Context->getSourceManager();
    if (!SM.isWrittenInMainFile(CStyleCast->getExprLoc()))
      return true;

    LangOptions LangOpts;
    std::string ReplacementText =
        (llvm::Twine("static_cast<") +
         CStyleCast->getTypeAsWritten().getAsString() + ">(" +
         Lexer::getSourceText(CharSourceRange::getTokenRange(
                                  CStyleCast->getSubExpr()->getSourceRange()),
                              SM, LangOpts) +
         ")")
            .str();

    // The hint carries the edit alongside the diagnostic rather than applying it,
    // so the same tool can report, preview or apply the change.
    FixItHint Hint = FixItHint::CreateReplacement(CStyleCast->getSourceRange(), ReplacementText);

    DiagnosticsEngine &Diags = Context->getDiagnostics();
    unsigned DiagID = Diags.getCustomDiagID(DiagnosticsEngine::Warning,
                                            "use a C++ cast instead of a C-style cast");
    Diags.Report(CStyleCast->getBeginLoc(), DiagID) << Hint;
    return true;
  }

private:
  ASTContext *Context;
};

class FixItCastConsumer : public ASTConsumer {
public:
  explicit FixItCastConsumer(ASTContext *Context) : Visitor(Context) {}
  void HandleTranslationUnit(ASTContext &Context) override {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  FixItCastVisitor Visitor;
};

#endif // REWRITE_CAST_FIXIT_H
