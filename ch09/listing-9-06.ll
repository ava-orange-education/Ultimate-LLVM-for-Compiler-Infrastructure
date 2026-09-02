; Listing 9-6. Loop-invariant and loop-variant instructions side by side
; Run: opt -passes=verify -S listing-9-06.ll -o /dev/null

define void @example(ptr %p, i32 %a) {
entry:
; Inside loop body:
%b    = load i32, ptr %p      ; loop-variant: reloaded every iteration
%temp = add i32 %a, 10        ; %a is defined outside the loop, so this is invariant
%result = mul i32 %temp, %b   ; not invariant: it depends on %b

  ret void
}
