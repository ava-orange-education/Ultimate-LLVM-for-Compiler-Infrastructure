; Listing 10-1. A loop that loads and stores on every iteration
; Run: opt -passes=verify -S listing-10-01.ll -o /dev/null

define void @copy_forever(ptr %ptr, ptr %ptr2) {
entry:
  br label %loop

loop:
  %x = load i32, ptr %ptr
  store i32 %x, ptr %ptr2
  br label %loop
}
