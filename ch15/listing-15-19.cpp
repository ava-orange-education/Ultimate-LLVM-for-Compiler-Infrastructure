// Listing 15-19. SmallVector: stack storage for small collections
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-15-19.cpp

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"

using namespace llvm;

// Stack storage for <=4 elements
SmallVector<Value *, 4> Operands;
SmallVector<Instruction *> Instrs; // Heap fallback when needed

// Efficient collection building. `User` is the type, so the range comes from an
// instance of it. operands() yields Use objects, which cannot be copied into a
// vector; operand_values() yields the Value* the book is after.
inline auto getUses(User *U) {
  return to_vector(U->operand_values()); // Helper converts ranges
}

// Size optimizations
static_assert(sizeof(SmallVector<int, 0>) < sizeof(std::vector<int>));
