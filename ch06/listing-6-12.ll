; Listing 6-12. A function's basic blocks
; Run: opt -passes=verify -S listing-6-12.ll -o /dev/null

define i32 @example(i32 %a, i32 %b) {
entry:
    %sum = add i32 %a, %b
    br label %exit  ; Branch to exit block
exit:
    ret i32 %sum
}
