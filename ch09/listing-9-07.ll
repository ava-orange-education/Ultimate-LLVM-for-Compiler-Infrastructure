; Listing 9-7. The invariant add after LICM hoists it to the preheader
; Run: opt -passes=verify -S listing-9-07.ll -o /dev/null

; Loop-invariant code motion, after: the invariant add has been hoisted out of the
; loop and now runs once in the preheader.
;
; The book prints the two instructions on their own. A preheader and a loop are
; supplied here so the file assembles and so "hoisted to the preheader" is something
; the reader can see rather than take on trust.
define i32 @licm_after(i32 %a, i32 %b, i32 %n) {
entry:
  br label %preheader

preheader:
; In the loop preheader:
%temp = add i32 %a, 10
  br label %loop

loop:
  %i = phi i32 [ 0, %preheader ], [ %i.next, %loop ]

; Updated loop body. The loop labels and branches are left out to keep the
; point in view: only the placement of %temp has changed.
%result = mul i32 %temp, %b
  %i.next = add i32 %i, 1
  %cmp = icmp slt i32 %i.next, %n
  br i1 %cmp, label %loop, label %exit

exit:
  ret i32 %result
}
