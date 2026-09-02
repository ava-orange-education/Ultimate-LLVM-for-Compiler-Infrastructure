// irbuilder-basics.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only irbuilder-basics.cpp

// irbuilder-basics.cpp
//
// Building IR from C++: creating a function, folding two constants into an add, and
// walking an AST node to emit code for it. The chapter prints each as two or three
// statements, none of which has the LLVMContext, Module or IRBuilder they all need.
//
// There is deliberately no `using namespace llvm` here. The book's last argument to
// Function::Create is a variable spelled `Module`, and with the namespace open that
// name is ambiguous against llvm::Module. The listings qualify everything with llvm::
// anyway, so dropping the using-directive is what lets the printed lines stand
// unchanged.
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <memory>

// The toy AST the chapter lowers. GenerateCode is printed as a free function that
// calls Node->LHS->GenerateCode(), so the node type has to have that member too.
enum class ASTNodeType { Add, Literal };

struct ASTNode {
  ASTNodeType Type = ASTNodeType::Literal;
  ASTNode *LHS = nullptr;
  ASTNode *RHS = nullptr;
  llvm::Value *GenerateCode();
};

static llvm::LLVMContext Context;
// Function::Create takes a Module *, so this has to be a pointer; the owning
// unique_ptr is kept alongside it so nothing leaks.
static std::unique_ptr<llvm::Module> OwnedModule =
    std::make_unique<llvm::Module>("book", Context);
static llvm::Module *Module = OwnedModule.get();
static llvm::IRBuilder<> Builder(Context);

void create_function() {
  llvm::FunctionType *FuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), false);
  llvm::Function *Function = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "my_function", Module);
  llvm::BasicBlock *Entry = llvm::BasicBlock::Create(Context, "entry", Function);
  Builder.SetInsertPoint(Entry);
}

void build_addition() {
  llvm::Value *LHS = llvm::ConstantInt::get(Context, llvm::APInt(32, 5));
  llvm::Value *RHS = llvm::ConstantInt::get(Context, llvm::APInt(32, 10));
  llvm::Value *Sum = Builder.CreateAdd(LHS, RHS, "sum");
  (void)Sum;
}

llvm::Value *GenerateCode(ASTNode *Node) {
    if (Node->Type == ASTNodeType::Add) {
        return Builder.CreateAdd(Node->LHS->GenerateCode(), Node->RHS->GenerateCode(), "addtmp");
    }
    return nullptr;
}

llvm::Value *ASTNode::GenerateCode() { return ::GenerateCode(this); }
