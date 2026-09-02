; Listing 9-25. The same aggregate, repeated for the detailed walkthrough
; Run: opt -passes=verify -S listing-9-25.ll -o /dev/null

define void @example() {
entry:
%s = alloca { i32, i32 }, align 4
%p_x = getelementptr inbounds { i32, i32 }, ptr %s, i32 0, i32 0
%p_y = getelementptr inbounds { i32, i32 }, ptr %s, i32 0, i32 1
store i32 10, ptr %p_x, align 4
store i32 20, ptr %p_y, align 4
%val1 = load i32, ptr %p_x, align 4
%val2 = load i32, ptr %p_y, align 4
%sum = add i32 %val1, %val2

  ret void
}
