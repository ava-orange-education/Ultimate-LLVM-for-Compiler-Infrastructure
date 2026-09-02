; Listing 9-15. After inlining: the call has gone
; Run: opt -passes=verify -S listing-9-15.ll -o /dev/null

define void @example(i32 %x, i32 %y) {
entry:
%sum = add i32 %x, %y

  ret void
}
