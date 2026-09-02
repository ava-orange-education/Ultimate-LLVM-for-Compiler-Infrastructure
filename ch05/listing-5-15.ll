; Listing 5-15. A block and the terminator that ends it
; Run: opt -passes=verify -S listing-5-15.ll -o /dev/null

define void @example() {
entry:
  %val = add i32 1, 2
  br label %end
end:
  ret void
}
