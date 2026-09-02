; Listing 6-26. The fast calling convention
; Run: opt -passes=verify -S listing-6-26.ll -o /dev/null

define fastcc i32 @fast_call(i32 %a, i32 %b) {
    %sum = add i32 %a, %b
    ret i32 %sum
}
