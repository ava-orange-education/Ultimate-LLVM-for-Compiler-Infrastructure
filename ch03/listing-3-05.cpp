// Listing 3-5. The headers a standalone Clang lexer needs
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-3-05.cpp

#include <clang/Basic/Diagnostic.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/LangOptions.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include <llvm/Support/raw_ostream.h>
#include <cstring>

void LexSourceCode(const char *sourceCode, clang::LangOptions &langOpts) {
    // FileManager caches every file Clang opens, so a header pulled in twice is read
    // once. FileSystemOptions is its configuration -- chiefly the working directory
    // relative paths resolve against; the default is enough when the source is already
    // in memory, as it is here.
    clang::FileManager fileMgr{clang::FileSystemOptions()};
    // DiagnosticsEngine has no default constructor: every diagnostic needs an id table
    // and a set of options. The ids are reference-counted and the options are not --
    // the engine takes them by reference, so diagOpts has to outlive it.
    llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> diagIDs(new clang::DiagnosticIDs());
    clang::DiagnosticOptions diagOpts;
    clang::DiagnosticsEngine diags(diagIDs, diagOpts);
    // SourceManager owns the buffers and turns a SourceLocation -- which is just an
    // offset -- into a file, line and column. It needs the FileManager to find files
    // and the DiagnosticsEngine to report one it cannot read, which is why both are
    // built first.
    clang::SourceManager srcMgr(diags, fileMgr);
    clang::SourceLocation startLoc = srcMgr.getLocForStartOfFile(srcMgr.getMainFileID());
    clang::Lexer Lexer(startLoc, langOpts, sourceCode, sourceCode,
                       sourceCode + strlen(sourceCode));
    clang::Token token;
    // Lexer::LexFromRawLexer returns true at end of file, so the loop runs until it
    // does. Lexer::Lex is the Preprocessor-facing entry point and is not what a
    // standalone raw lexer calls.
    while (!Lexer.LexFromRawLexer(token)) {
        llvm::outs() << "Token Type: " << token.getName()
                     << ", Location: " << token.getLocation().printToString(srcMgr) << "\n";
    }
}
