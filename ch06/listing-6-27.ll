; Listing 6-27. A guaranteed tail call
; Run: opt -passes=verify -S listing-6-27.ll -o /dev/null

; musttail marks the call, not the function: it is a guarantee about this one
; call site, which must be followed immediately by a ret of its result.
define i32 @tail_recursive(i32 %n) {
    %next = sub i32 %n, 1
    %result = musttail call i32 @tail_recursive(i32 %next)
    ret i32 %result
}
