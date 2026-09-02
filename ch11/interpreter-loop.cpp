// interpreter-loop.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only interpreter-loop.cpp

// interpreter-loop.cpp
//
// The interpreter's dispatch loop, and the tiering policy that decides how hard to
// optimise a function. Both are printed as bodies with nothing declared around them:
// the loop refers to an ExecutionStack, a GenericValue stack and three helpers that
// exist only in the chapter's narrative, and the policy calls two pipeline functions
// that are never defined.
//
// This is an illustration of how an interpreter is shaped, not LLVM's own Interpreter
// -- llvm::Interpreter drives visit() from InstVisitor rather than a switch on
// getOpcode(). The class is declared here so the printed body compiles as written.
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/Instruction.h"

#include <map>
#include <string>
#include <vector>

using namespace llvm;

class Interpreter {
public:
  void run();

private:
  Instruction *getCurrentInstruction();
  void advanceToNextInstruction();
  GenericValue pop();
  void push(GenericValue V);

  std::vector<GenericValue> ExecutionStack;
};

void Interpreter::run() {
  while (!ExecutionStack.empty()) {
    Instruction *I = getCurrentInstruction();
    switch (I->getOpcode()) {
      case Instruction::Add: {
        // Fetch operands from simulated stack
        GenericValue lhs = pop();
        GenericValue rhs = pop();
        GenericValue result;
        result.IntVal = lhs.IntVal + rhs.IntVal;
        push(result);
        break;
      }
      case Instruction::Ret: {
        // Handle return value
        break;
      }
      // ... other instruction types
    }
    advanceToNextInstruction();
  }
}

// Tiering: a function that has been called only a few times is compiled quickly, and
// one that is hot earns the expensive pipeline.
static std::map<std::string, unsigned> CallCount;
static unsigned Threshold = 100;
static void UseFastPipeline();
static void UseAggressivePipeline();

void choose_pipeline(const std::string &FnName) {
  if (CallCount[FnName] < Threshold)
      UseFastPipeline();
  else
      UseAggressivePipeline();
}
