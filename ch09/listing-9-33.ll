; Listing 9-33. After: %3 replaced by %1
; Run: opt -passes=verify -S listing-9-33.ll -o /dev/null

define void @example(i32 %a, i32 %b, i32 %c, i32 %d) {
entry:
%1 = add i32 %a, %b
%2 = sub i32 %c, %d
; Replace %3 with %1
; All subsequent uses that refer to %3 now refer to %1.

  ret void
}
