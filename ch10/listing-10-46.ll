; Listing 10-46. The name as it appears in the IR
; Run: opt -passes=verify -S listing-10-46.ll -o /dev/null

define i32 @scale(i32 %x, i32 %y) {
entry:
  %scaled_val = mul i32 %x, %y
  ret i32 %scaled_val
}
