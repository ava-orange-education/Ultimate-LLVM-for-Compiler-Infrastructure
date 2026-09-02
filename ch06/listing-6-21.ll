; Listing 6-21. A function carrying an attribute group

define i32 @fast_add(i32 %a, i32 %b) #0 {
entry:
    %sum = add i32 %a, %b
    ret i32 %sum
}
#0 refers to an attribute set, which may include optimizations like noinline, alwaysinline, or noreturn.
