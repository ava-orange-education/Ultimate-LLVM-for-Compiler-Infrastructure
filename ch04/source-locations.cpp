// source-locations.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only source-locations.cpp

// source-locations.cpp
//
// The four SourceManager queries the chapter shows as one-liners: presumed location,
// decomposed location, spelling location and expansion location. They are printed
// separately because each answers a different question, but they only make sense
// against a real SourceManager, so this is the program they were lifted out of.
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

static void describe(SourceManager &SourceMgr, SourceLocation SomeLoc) {
  // A presumed location honours #line directives, so it is what a diagnostic
  // should print: the file, line and column the programmer believes they are in.
  PresumedLoc PLoc = SourceMgr.getPresumedLoc(SomeLoc);
  if (PLoc.isValid()) {

      llvm::outs() << "File: " << PLoc.getFilename()
                   << ", Line: " << PLoc.getLine()
                   << ", Column: " << PLoc.getColumn() << "\n";
  }

  // Decomposing splits the opaque location into the buffer it lives in and a byte
  // offset within that buffer -- the form the SourceManager stores internally.
  std::pair<FileID, unsigned> DecomposedLoc = SourceMgr.getDecomposedLoc(SomeLoc);
  FileID FID = DecomposedLoc.first;
  unsigned Offset = DecomposedLoc.second;
  llvm::outs() << "Offset " << Offset << " in file id " << FID.getHashValue() << "\n";

  // For a location inside a macro expansion the spelling location is where the
  // text was physically written -- inside the macro definition.
  SourceLocation SpellingLoc = SourceMgr.getSpellingLoc(SomeLoc);

  // ... and the expansion location is where the macro was used.
  SourceLocation ExpansionLoc = SourceMgr.getExpansionLoc(SomeLoc);

  llvm::outs() << "spelled at line "
               << SourceMgr.getSpellingLineNumber(SpellingLoc)
               << ", expanded at line "
               << SourceMgr.getSpellingLineNumber(ExpansionLoc) << "\n";
}

namespace {
class LocationVisitor : public RecursiveASTVisitor<LocationVisitor> {
public:
  explicit LocationVisitor(ASTContext *Context) : Context(Context) {}

  bool VisitFunctionDecl(FunctionDecl *FD) {
    SourceManager &SourceMgr = Context->getSourceManager();
    SourceLocation SomeLoc = FD->getLocation();
    if (SourceMgr.isWrittenInMainFile(SomeLoc))
      describe(SourceMgr, SomeLoc);
    return true;
  }

private:
  ASTContext *Context;
};

class LocationConsumer : public ASTConsumer {
public:
  explicit LocationConsumer(ASTContext *Context) : Visitor(Context) {}
  void HandleTranslationUnit(ASTContext &Context) override {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  LocationVisitor Visitor;
};

class LocationAction : public ASTFrontendAction {
public:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 llvm::StringRef) override {
    return std::make_unique<LocationConsumer>(&CI.getASTContext());
  }
};
} // namespace

static llvm::cl::OptionCategory ToolCategory("source-locations options");

int main(int argc, const char **argv) {
  auto ExpectedParser = tooling::CommonOptionsParser::create(argc, argv, ToolCategory);
  if (!ExpectedParser) {
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }
  tooling::CommonOptionsParser &OptionsParser = ExpectedParser.get();
  tooling::ClangTool Tool(OptionsParser.getCompilations(),
                          OptionsParser.getSourcePathList());
  return Tool.run(tooling::newFrontendActionFactory<LocationAction>().get());
}
