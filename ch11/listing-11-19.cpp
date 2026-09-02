// Listing 11-19. A compiler that can run on several threads
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-11-19.cpp

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/IRTransformLayer.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/Orc/Shared/ExecutorAddress.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/TargetSelect.h"
using namespace llvm; using namespace llvm::orc;
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

auto JTMB = cantFail(JITTargetMachineBuilder::detectHost());
auto Compiler = std::make_unique<orc::ConcurrentIRCompiler>(JTMB);
