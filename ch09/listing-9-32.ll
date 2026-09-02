; Listing 9-32. Before: %3 recomputes what %1 already holds
; Run: opt -passes=verify -S listing-9-32.ll -o /dev/null

define void @example(i32 %a, i32 %b, i32 %c, i32 %d) {
entry:
%1 = add i32 %a, %b         ; compute %a + %b
%2 = sub i32 %c, %d
%3 = add i32 %a, %b         ; computed again

  ret void
}
