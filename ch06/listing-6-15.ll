; Listing 6-15. Each value assigned exactly once
; Run: opt -passes=verify -S listing-6-15.ll -o /dev/null

define i32 @ssa_example(i32 %a, i32 %b) {
    %x1 = add i32 %a, %b  ; First version of x
    %x2 = mul i32 %x1, 2  ; Second version of x
    ret i32 %x2
}
