; Listing 6-25. The default calling convention
; Run: opt -passes=verify -S listing-6-25.ll -o /dev/null

; The calling convention goes before the return type, not after the parameters.
define ccc i32 @default_call(i32 %a, i32 %b) {
    %sum = add i32 %a, %b
    ret i32 %sum
}
