; Listing 12-17. The same IR node, for the GlobalISel comparison
; Run: opt -passes=verify -S listing-12-17.ll -o /dev/null

define void @example(i32 %a) {
entry:
%sum = add i32 %a, 42

  ret void
}
