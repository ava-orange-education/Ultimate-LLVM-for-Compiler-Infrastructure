; Listing 6-13. A conditional branch
; Run: opt -passes=verify -S listing-6-13.ll -o /dev/null

define void @conditional_example(i1 %cond) {
entry:
    br i1 %cond, label %true_block, label %false_block
true_block:
    ret void
false_block:
    ret void
}
