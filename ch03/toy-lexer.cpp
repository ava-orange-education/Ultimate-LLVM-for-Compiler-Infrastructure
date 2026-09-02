// toy-lexer.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only toy-lexer.cpp

// toy-lexer.cpp
//
// Driving Clang's Lexer directly: construct one over a buffer, pull tokens out until
// it runs dry, and report a bad character at the location it was found. The chapter
// prints each step on its own, and none of them has the SourceManager, LangOptions or
// buffer pointers in scope that they all depend on.
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Lex/Lexer.h"
#include "llvm/Support/raw_ostream.h"

void lex_main_file(clang::SourceManager &srcMgr, const clang::LangOptions &langOpts,
                   const char *bufferStart, const char *bufferEnd) {
  clang::SourceLocation startLoc = srcMgr.getLocForStartOfFile(srcMgr.getMainFileID());
  clang::Lexer toy_Lexer(startLoc, langOpts, bufferStart, bufferStart, bufferEnd);

  // Lex() returns true at end of file, so the loop runs while it returns false.
  clang::Token token;
  while (!toy_Lexer.Lex(token)) {
      llvm::outs() << "Token: " << token.getName() << "\n";
  }
}

// The chapter is building a toy front end, so its diagnostics are its own. Clang 22
// has no diag::err_invalid_character -- the closest names in its generated tables are
// err_invalid_character_udl and err_invalid_character_to_charify, both about character
// literals -- so a reader who expects to find this id in Clang will not. Declaring the
// id here is what the printed line assumes: a front end defines its own table and
// reports against it exactly like this.
namespace diag {
enum : unsigned { err_invalid_character = 1 };
} // namespace diag

namespace {
struct Reporter {
  clang::DiagnosticsEngine &Diags;

  clang::DiagnosticBuilder Diag(clang::SourceLocation Loc, unsigned ID) {
    return Diags.Report(Loc, ID);
  }

  void report(const clang::Token &token, char offendingChar) {
    Diag(token.getLocation(), diag::err_invalid_character) << offendingChar;
  }
};
} // namespace
