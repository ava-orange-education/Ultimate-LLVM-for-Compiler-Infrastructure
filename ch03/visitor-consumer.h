// visitor-consumer.h -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only visitor-consumer.h

// visitor-consumer.h
//
// The ASTConsumer that runs a RecursiveASTVisitor over the translation unit. The book
// prints the consumer alone; the visitor it holds and traverses with is what makes it
// compile, and HandleTranslationUnit is the hook that gets the whole unit in one go.
#ifndef VISITOR_CONSUMER_H
#define VISITOR_CONSUMER_H

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "llvm/Support/raw_ostream.h"

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
public:
  bool VisitFunctionDecl(clang::FunctionDecl *FD) {
    llvm::outs() << "function: " << FD->getNameAsString() << "\n";
    return true;
  }
};

class MyASTConsumer : public clang::ASTConsumer {
    MyASTVisitor Visitor;
public:
    void HandleTranslationUnit(clang::ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }
};

#endif // VISITOR_CONSUMER_H
