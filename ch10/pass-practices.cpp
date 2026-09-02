// pass-practices.cpp -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only pass-practices.cpp

// pass-practices.cpp
//
// The "pitfalls and practices" section prints its advice as one- and two-line
// snippets: set an insert point before building, abandon an analysis you invalidated,
// re-query rather than hold a stale result, carry the debug location onto a clone,
// tell scalar evolution what moved, and verify before returning. Each is a statement
// with no function around it, so this is the pass they all come from.
//
// Two of that section's snippets are deliberately not here. `FPM.addPass(
// LoopPassManagerWrapper())` is printed as the wrong way to nest a loop pass -- no
// such class exists, which is the point -- and `Module *M1 = new Module(...,
// Context1)` has a literal ellipsis for the module identifier, so it is pseudo-code.
#include "llvm/Analysis/CFGPrinter.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"

using namespace llvm;

struct MyLoopPass : PassInfoMixin<MyLoopPass> {
  PreservedAnalyses run(Loop &L, LoopAnalysisManager &AM,
                        LoopStandardAnalysisResults &AR, LPMUpdater &U) {
    return PreservedAnalyses::all();
  }
};

// A builder with no insert point has nowhere to put what it makes.
void build_safely(IRBuilder<> &B, BasicBlock *SomeBB, Value *X, Value *Y) {
  B.SetInsertPoint(SomeBB);
  Value *V = B.CreateAdd(X, Y); // safe
  (void)V;
}

void erase_one(Instruction *I) {
  I->eraseFromParent();
}

void erase_one_named(Instruction *Inst) {
  Inst->eraseFromParent(); // safe deletion
}

// Changing the CFG invalidates the dominator tree even if nothing else moved.
PreservedAnalyses after_cfg_change() {
  return PreservedAnalyses::all().abandon<DominatorTreeAnalysis>();
}

// The stale-result mistake: LI is captured and then kept across a mutation.
void holding_a_stale_result(Function &F, FunctionAnalysisManager &FAM) {
  LoopInfo *LI = &FAM.getResult<LoopAnalysis>(F);
  // Later: modifies loop structure
  // But still uses old LI!
  (void)LI;
}

// The fix: abandon the analysis, then ask again.
//
// Asking a second time is not enough. getResult runs the analysis only on a cache
// miss, so the second call finds the entry already there and hands back the same
// stale LoopInfo -- measured: after deleting a loop's backedge, a plain re-query
// still reports the loop. The cached entry has to go first.
void re_query(Function &F, FunctionAnalysisManager &FAM) {
  auto &LI = FAM.getResult<LoopAnalysis>(F);
  // ... mutation happens ...
  PreservedAnalyses PA;
  PA.abandon<LoopAnalysis>();
  FAM.invalidate(F, PA);
  auto &NewLI = FAM.getResult<LoopAnalysis>(F);
  (void)LI;
  (void)NewLI;
}

// The adapter that actually exists, as opposed to the invented wrapper class.
void nest_a_loop_pass(FunctionPassManager &FPM) {
  FPM.addPass(createFunctionToLoopPassAdaptor(MyLoopPass()));
}

PreservedAnalyses preserved_nothing() {
  return PreservedAnalyses::none(); // if IR was changed extensively
}

PreservedAnalyses preserved_cfg_only() {
  return PreservedAnalyses::allInSet<CFGAnalyses>();
}

void clone_with_location(Instruction *OldInst) {
  Instruction *NewInst = OldInst->clone();
  NewInst->setDebugLoc(OldInst->getDebugLoc());
  NewInst->insertBefore(OldInst->getIterator());
}

void tell_scalar_evolution(ScalarEvolution *SE, Loop *OldLoop, Instruction *MutatedInst) {
  SE->forgetLoop(OldLoop);
  // The book calls SE->forgetInstruction(). ScalarEvolution has no such member: the
  // one that drops a cached SCEV for a single value is forgetValue(Value *)
  // (ScalarEvolution.h:994). forgetLoop on the line above is spelled correctly, which
  // is what makes the pair read as right.
  SE->forgetValue(MutatedInst);
}

void hoist_if_safe(Instruction *I) {
  if (isSafeToSpeculativelyExecute(I))
    // safe to hoist or duplicate
    return;
}

// Rewiring the CFG by hand, and tearing a block down before erasing it.
void rewire(BasicBlock *NewTrueBB, BasicBlock *NewFalseBB, Value *Cond,
            IRBuilder<> &Builder, BasicBlock *DeadBB) {
  // Rewire a conditional branch safely: edit the terminator the block already has.
  // BranchInst::Create with a BasicBlock* as its last argument *appends* to that
  // block, and the block already ends in a terminator -- so creating one here
  // leaves two and verifyFunction rejects the function. This is the chapter's own
  // advice, "use BranchInst::setSuccessor() to change the branch target".
  auto *BI = cast<BranchInst>(Builder.GetInsertBlock()->getTerminator());
  BI->setCondition(Cond);
  BI->setSuccessor(0, NewTrueBB);
  BI->setSuccessor(1, NewFalseBB);

  // Deleting a block is not "drop what it points at, then erase". That leaves every
  // predecessor still branching to DeadBB and every phi still naming it, so the
  // block is still a used Value and eraseFromParent hits "Uses remain when a value
  // is destroyed!". DeleteDeadBlock does the whole job; its precondition is that
  // the block has no predecessors left.
  DeleteDeadBlock(DeadBB);
}

PreservedAnalyses verify_before_returning(Function *F) {
  if (verifyFunction(*F, &errs())) {
    errs() << "Verification failed!\n";
    return PreservedAnalyses::none();
  }
  return PreservedAnalyses::all();
}
