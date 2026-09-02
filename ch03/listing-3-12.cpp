// Listing 3-12. Visiting every function declaration
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-3-12.cpp

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/RecursiveASTVisitor.h"
using namespace clang; using namespace clang::ast_matchers;
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
using namespace llvm;

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
public:
    bool VisitFunctionDecl(clang::FunctionDecl *FD) {
        llvm::outs() << "Function: " << FD->getNameAsString() << "\n";
        return true; // Continue traversal
    }
};
