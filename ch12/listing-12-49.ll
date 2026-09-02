; Listing 12-49. A test input for the new backend
; Run: opt -passes=verify -S listing-12-49.ll -o /dev/null

; test_add.ll
define i32 @add(i32 %a, i32 %b) {
  %sum = add i32 %a, %b
  ret i32 %sum
}
