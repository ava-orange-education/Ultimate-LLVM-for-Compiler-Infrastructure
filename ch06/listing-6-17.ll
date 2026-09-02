; Listing 6-17. A value held in a virtual register
; Run: opt -passes=verify -S listing-6-17.ll -o /dev/null

define i32 @optimized(i32 %a, i32 %b) {
    %sum = add i32 %a, %b  ; Stored in a virtual register
    ret i32 %sum
}
