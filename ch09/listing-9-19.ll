; Listing 9-19. Before: the same addition computed twice
; Run: opt -passes=verify -S listing-9-19.ll -o /dev/null

define void @example(i32 %a, i32 %b) {
entry:
%1 = add i32 %a, %b
%2 = add i32 %a, %b
%3 = mul i32 %1, 2
%4 = mul i32 %2, 2

  ret void
}
