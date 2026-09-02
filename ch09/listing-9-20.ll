; Listing 9-20. After: the second use redirected to the first
; Run: opt -passes=verify -S listing-9-20.ll -o /dev/null

define void @example(i32 %a, i32 %b) {
entry:
%1 = add i32 %a, %b
%3 = mul i32 %1, 2
%4 = mul i32 %1, 2   ; replaced %2 with %1

  ret void
}
