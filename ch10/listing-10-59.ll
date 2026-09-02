; Listing 10-59. A PHI left naming a removed predecessor
; Run: opt -passes=verify -S listing-10-59.ll -o /dev/null

; WRONG ON PURPOSE. A predecessor was removed from the CFG but its incoming
; value was left in the PHI, so the PHI still names a block that no longer
; branches here. Note that LLVM IR comments start with a semicolon; // is a
; parse error, not a comment.
;
; opt -passes=verify rejects this with:
;   PHINode should have one entry for each predecessor of its parent basic block!

define i32 @f(i1 %c, i32 %a, i32 %b) {
entry:
  br i1 %c, label %new_pred, label %merge

new_pred:
  br label %merge

merge:
  %phi = phi i32 [ %a, %old_pred ], [ %b, %new_pred ]
  ret i32 %phi

old_pred:
  br label %merge
}
