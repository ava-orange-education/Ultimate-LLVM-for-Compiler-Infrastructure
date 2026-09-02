; Listing 6-18. A computation nothing uses
; Run: opt -passes=verify -S listing-6-18.ll -o /dev/null

define i32 @dead_code_example(i32 %a) {
    %x = add i32 %a, 5  ; Unused computation
    ret i32 %a
}
