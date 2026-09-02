; Listing 6-14. A loop built from blocks and branches
; Run: opt -passes=verify -S listing-6-14.ll -o /dev/null

define void @loop_example(i32 %n) {
entry:
    %i = alloca i32
    store i32 0, ptr %i
    br label %loop
loop:
    %val = load i32, ptr %i
    %cond = icmp slt i32 %val, %n
    br i1 %cond, label %body, label %exit
body:
    %new_val = add i32 %val, 1
    store i32 %new_val, ptr %i
    br label %loop
exit:
    ret void
}
