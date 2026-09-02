; Listing 5-4. A reassigned variable, rewritten in SSA form
; Run: opt -passes=verify -S listing-5-04.ll -o /dev/null

define void @example(i32 %a, i32 %b, i32 %c) {
entry:
%x1 = add i32 %a, %b
%x2 = mul i32 %x1, %c

  ret void
}
