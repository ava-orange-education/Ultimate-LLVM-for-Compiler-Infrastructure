// memory-cookbook.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only memory-cookbook.cpp

// memory-cookbook.cpp
//
// The memory-analysis queries the chapter prints one at a time: asking MemorySSA what
// clobbers a load, asking alias analysis whether a call touches memory, refusing to
// move volatile or atomic accesses, and forwarding a store to a load that must alias
// it. They are shown as bare conditions; this is the pass that supplies the analyses
// and the instructions they talk about.
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/MemorySSA.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace {
struct MemoryCookbook : PassInfoMixin<MemoryCookbook> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    MemorySSA *MSSA = &FAM.getResult<MemorySSAAnalysis>(F).getMSSA();
    AAResults *AA = &FAM.getResult<AAManager>(F);
    DominatorTree *DT = &FAM.getResult<DominatorTreeAnalysis>(F);
    LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);

    LoadInst *LoadInstPtr = nullptr;
    StoreInst *StoreInstPtr = nullptr;
    CallInst *CallInstPtr = nullptr;
    for (BasicBlock &BB : F)
      for (Instruction &I : BB) {
        if (!LoadInstPtr)
          LoadInstPtr = dyn_cast<LoadInst>(&I);
        if (!StoreInstPtr)
          StoreInstPtr = dyn_cast<StoreInst>(&I);
        if (!CallInstPtr)
          CallInstPtr = dyn_cast<CallInst>(&I);
      }
    if (!LoadInstPtr || !StoreInstPtr || !CallInstPtr)
      return PreservedAnalyses::all();
    Loop *Loop = LI.getLoopFor(LoadInstPtr->getParent());
    if (!Loop)
      return PreservedAnalyses::all();

    // The clobbering access is the last thing that could have written what this load
    // reads. If it lies outside the loop, nothing in the loop can change the value.
    MemoryAccess *LoadAccess = MSSA->getMemoryAccess(LoadInstPtr);
    MemoryAccess *Clobber = MSSA->getWalker()->getClobberingMemoryAccess(LoadAccess);

    if (Clobber && !Loop->contains(Clobber->getBlock())) {
      // No store inside loop clobbers this load, safe to hoist
    }

    // MemoryEffects replaced the old onlyReadsMemory/doesNotAccessMemory predicates.
    MemoryEffects ME = AA->getMemoryEffects(CallInstPtr);
    if (ME.doesNotAccessMemory()) {
      // Call has no side effects, safe to reorder or remove if unused
    }

    for (BasicBlock &BB : F)
      for (Instruction &I : BB) {
        if (I.isVolatile() || I.isAtomic()) {
          // Skip transformations that reorder or remove this instruction
          continue;
        }
      }

    // MustAlias plus program order is NOT enough to make forwarding sound, and
    // comesBefore cannot even express the general case: it asserts unless both
    // instructions are in the same block, while the store that matters usually
    // dominates the load from another block. Nor does the pair rule out an
    // intervening write -- "store p,1; store p,2; load p" satisfies both and
    // forwards 1.
    //
    // Dominance is the ordering that holds across blocks, and MemorySSA answers
    // the clobber question directly: forward only when the store that must alias
    // is the access the walker names as clobbering this load.
    MemoryAccess *LoadClobber =
        MSSA->getWalker()->getClobberingMemoryAccess(LoadInstPtr);
    if (auto *ClobberDef = dyn_cast<MemoryDef>(LoadClobber))
      if (ClobberDef->getMemoryInst() == StoreInstPtr &&
          DT->dominates(StoreInstPtr, LoadInstPtr) &&
          AA->alias(LoadInstPtr->getPointerOperand(),
                    StoreInstPtr->getPointerOperand()) == AliasResult::MustAlias) {
        LoadInstPtr->replaceAllUsesWith(StoreInstPtr->getValueOperand());
        LoadInstPtr->eraseFromParent();
      }

    return PreservedAnalyses::none();
  }
};
} // namespace
