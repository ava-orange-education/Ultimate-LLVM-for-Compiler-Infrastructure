// Listing 10-38. Forwarding a store to a load that must alias it

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
