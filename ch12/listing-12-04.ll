; Listing 12-4. The IR the instruction selector will match
; Run: opt -passes=verify -S listing-12-04.ll -o /dev/null

define i32 @add_const(i32 %a) {
entry:
  %sum = add i32 %a, 42
  ret i32 %sum
}
