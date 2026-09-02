// clangtool-setup.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only clangtool-setup.cpp

// clangtool-setup.cpp
//
// Building a ClangTool by hand: load a compilation database from a directory rather
// than letting CommonOptionsParser find it, then add a flag to every compilation the
// tool runs. The chapter prints each as one or two lines with no declarations around
// them, and loadFromDirectory's error string parameter is easy to miss when the call
// is shown on its own.
//
// The book writes "auto *Compilations". loadFromDirectory returns
// std::unique_ptr<CompilationDatabase> (CompilationDatabase.h:104), so declaring a
// pointer does not compile; it is plain "auto", and *Compilations on the next line
// works unchanged either way.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/ArgumentsAdjusters.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"

#include <string>
#include <vector>

int run_tool(const std::vector<std::string> &SourceFiles) {
  std::string ErrorMessage;
  auto Compilations = clang::tooling::CompilationDatabase::loadFromDirectory("path/to/compile_commands.json", ErrorMessage);
  if (!Compilations) {
    llvm::errs() << ErrorMessage << "\n";
    return 1;
  }

  clang::tooling::ClangTool Tool(*Compilations, SourceFiles);

  // Adjusters run for every file the tool visits, which is how a flag reaches
  // compilations the database already fixed.
  Tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-Wall"));

  return Tool.run(
      clang::tooling::newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}
