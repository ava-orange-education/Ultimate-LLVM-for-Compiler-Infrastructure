// Listing 2-12. A program that builds a module
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only listing-2-12.cpp

   #include <llvm/IR/LLVMContext.h>
   #include <llvm/IR/Module.h>
   #include <llvm/IR/IRBuilder.h>
   #include <llvm/Support/raw_ostream.h>

   int main() {
       llvm::LLVMContext Context;
       llvm::Module *Module = new llvm::Module("my_module", Context);
       llvm::IRBuilder<> Builder(Context);

       // Create the main function
       llvm::FunctionType *FunctionType = llvm::FunctionType::get(Builder.getInt32Ty(), false);
       llvm::Function *MainFunction = llvm::Function::Create(FunctionType, llvm::Function::ExternalLinkage, "main", Module);

       // Create a basic block
       llvm::BasicBlock *Entry = llvm::BasicBlock::Create(Context, "entry", MainFunction);
       Builder.SetInsertPoint(Entry);

       // Create a return statement
       Builder.CreateRet(Builder.getInt32(0));

       // Print the module
       Module->print(llvm::outs(), nullptr);
       delete Module;

       return 0;
   }
