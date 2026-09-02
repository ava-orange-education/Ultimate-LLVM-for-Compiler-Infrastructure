; Listing 6-20. A function definition
; Run: opt -passes=verify -S listing-6-20.ll -o /dev/null

define i32 @add(i32 %a, i32 %b) {
entry:
    %sum = add i32 %a, %b
    ret i32 %sum
}
