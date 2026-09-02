; Listing 9-29. After mem2reg: the variable lives in a register
; Run: opt -passes=verify -S listing-9-29.ll -o /dev/null

define i32 @computeSum(i32 %a, i32 %b) {
entry:
  %sum = add i32 %a, %b    ; Compute a + b.
  ret i32 %sum             ; Return the result directly.
}
