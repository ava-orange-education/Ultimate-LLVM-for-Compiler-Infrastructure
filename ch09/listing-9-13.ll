; Listing 9-13. The callee, marked alwaysinline
; Run: opt -passes=verify -S listing-9-13.ll -o /dev/null

; Callee: add
define i32 @add(i32 %a, i32 %b) alwaysinline {
  %sum = add i32 %a, %b
  ret i32 %sum
}
