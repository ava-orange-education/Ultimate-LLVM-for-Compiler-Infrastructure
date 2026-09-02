; Listing 9-1. An addition of zero, before folding
; Run: opt -passes=verify -S listing-9-01.ll -o /dev/null

define void @example(i32 %x) {
entry:
; Original IR
%result = add i32 %x, 0

  ret void
}
