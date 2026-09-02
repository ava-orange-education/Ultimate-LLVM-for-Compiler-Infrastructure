; Listing 9-9. The same load after LICM moves it to the preheader
; Run: opt -passes=verify -S listing-9-09.ll -o /dev/null

; The same loop-invariant load, after: LICM has moved it into the preheader, so it
; runs once however many times the loop goes round.
;
; As in licm-load-before.ll, %globalConst is a ptr parameter so that the printed line
; is reproduced exactly.
define i32 @licm_load_after(ptr %globalConst, i32 %n) {
entry:
  br label %preheader

preheader:
; In the preheader, loaded once:
%val = load i32, ptr %globalConst
  br label %loop

loop:
; The loop body now uses the value already in hand.
  %i = phi i32 [ 0, %preheader ], [ %i.next, %loop ]
  %acc = phi i32 [ 0, %preheader ], [ %sum, %loop ]
  %sum = add i32 %acc, %val
  %i.next = add i32 %i, 1
  %cmp = icmp slt i32 %i.next, %n
  br i1 %cmp, label %loop, label %exit

exit:
  ret i32 %sum
}
