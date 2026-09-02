; Listing 9-8. A loop-invariant load, before LICM
; Run: opt -passes=verify -S listing-9-08.ll -o /dev/null

; A loop-invariant load, before: the load sits in the loop body and is repeated on
; every iteration even though nothing in the loop writes through %globalConst.
;
; The book prints just the load. The loop around it is supplied here so the file
; assembles. %globalConst stays a local -- it is a ptr parameter, which is what the
; printed line reads it as; writing it @globalConst would assemble too but would no
; longer be the line the book prints.
define i32 @licm_load_before(ptr %globalConst, i32 %n) {
entry:
  br label %loop

loop:
  %i = phi i32 [ 0, %entry ], [ %i.next, %loop ]
  %acc = phi i32 [ 0, %entry ], [ %sum, %loop ]
; Inside the loop body, reloaded on every iteration:
%val = load i32, ptr %globalConst
; Subsequent computations use %val
  %sum = add i32 %acc, %val
  %i.next = add i32 %i, 1
  %cmp = icmp slt i32 %i.next, %n
  br i1 %cmp, label %loop, label %exit

exit:
  ret i32 %sum
}
