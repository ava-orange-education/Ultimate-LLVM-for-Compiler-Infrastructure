; Listing 5-12. The same function, labelled part by part
; Run: opt -passes=verify -S listing-5-12.ll -o /dev/null

define i32 @add(i32 %a, i32 %b) {
entry:
  %sum = add i32 %a, %b
  ret i32 %sum
}
