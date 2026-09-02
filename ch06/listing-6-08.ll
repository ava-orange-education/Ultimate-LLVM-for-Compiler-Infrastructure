; Listing 6-8. Values kept in registers rather than memory
; Run: opt -passes=verify -S listing-6-08.ll -o /dev/null

define i32 @register_example(i32 %a, i32 %b) {
    %sum = add i32 %a, %b  ; Computation result stored in a virtual register
    ret i32 %sum  ; No memory storage involved
}
