; Listing 6-29. Attributes written on the function itself
; Run: opt -passes=verify -S listing-6-29.ll -o /dev/null

define i32 @fast_add(i32 %a, i32 %b) alwaysinline nounwind {
    %sum = add i32 %a, %b
    ret i32 %sum
}
