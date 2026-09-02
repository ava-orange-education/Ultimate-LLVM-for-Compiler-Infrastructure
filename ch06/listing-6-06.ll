; Listing 6-6. A value produced by an instruction
; Run: opt -passes=verify -S listing-6-06.ll -o /dev/null

define void @example(i32 %a, i32 %b) {
entry:
%sum = add i32 %a, %b

  ret void
}
