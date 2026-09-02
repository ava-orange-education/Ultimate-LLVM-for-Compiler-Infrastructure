// Listing 10-10. Attaching the metadata to the back-edge
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-10-10.cpp

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

void attachLoopMetadata(BranchInst *BI, LLVMContext &Context) {
  // Metadata string tag
  MDString *Key = MDString::get(Context, "loop.has.sideeffects");
  // Create a metadata node: !{!"loop.has.sideeffects"}
  MDNode *LoopMD = MDNode::get(Context, {Key});
  // Wrap in another node as required by !llvm.loop
  MDNode *LoopAnnotation = MDNode::getDistinct(Context, {LoopMD});
  // Attach to branch instruction
  BI->setMetadata("llvm.loop", LoopAnnotation);
}
