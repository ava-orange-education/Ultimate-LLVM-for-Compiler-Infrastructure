; Listing 6-16. A phi node choosing by incoming edge
; Run: opt -passes=verify -S listing-6-16.ll -o /dev/null

define i32 @phi_example(i1 %cond, i32 %a, i32 %b) {
entry:
    br i1 %cond, label %true_block, label %false_block
true_block:
    %x1 = add i32 %a, 10
    br label %merge
false_block:
    %x2 = sub i32 %b, 5
    br label %merge
merge:
    %x = phi i32 [ %x1, %true_block ], [ %x2, %false_block ]
    ret i32 %x
}
