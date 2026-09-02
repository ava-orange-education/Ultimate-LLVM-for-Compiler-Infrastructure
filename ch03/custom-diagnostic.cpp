// custom-diagnostic.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only custom-diagnostic.cpp

// custom-diagnostic.cpp
//
// Emitting a diagnostic of your own from a tool. getCustomDiagID registers the message
// once and hands back an id; Report then takes that id and a location. The chapter
// prints the three lines without the ASTContext they all hang off.
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"

using namespace clang;

namespace {
class DiagnosingVisitor : public RecursiveASTVisitor<DiagnosingVisitor> {
public:
  explicit DiagnosingVisitor(ASTContext &Context) : Context(Context) {}

  bool VisitFunctionDecl(FunctionDecl *FD) {
    SourceLocation Location = FD->getLocation();
    if (!Context.getSourceManager().isWrittenInMainFile(Location))
      return true;

    DiagnosticsEngine &Diag = Context.getDiagnostics();
    unsigned ID = Diag.getCustomDiagID(DiagnosticsEngine::Warning, "Custom diagnostic message");
    Diag.Report(Location, ID);
    return true;
  }

private:
  ASTContext &Context;
};

class DiagnosingConsumer : public ASTConsumer {
public:
  void HandleTranslationUnit(ASTContext &Context) override {
    DiagnosingVisitor(Context).TraverseDecl(Context.getTranslationUnitDecl());
  }
};
} // namespace
