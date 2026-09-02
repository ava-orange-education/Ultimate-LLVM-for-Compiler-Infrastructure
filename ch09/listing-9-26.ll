; Listing 9-26. After SROA: one alloca per field
; Run: opt -passes=verify -S listing-9-26.ll -o /dev/null

define void @example() {
entry:
; Instead of a single alloca for the aggregate, separate allocas are created:
%p_x_scalar = alloca i32, align 4
%p_y_scalar = alloca i32, align 4

; The values are stored directly into each scalar
store i32 10, ptr %p_x_scalar, align 4
store i32 20, ptr %p_y_scalar, align 4

; The load operations now refer to the scalar variables
%val1 = load i32, ptr %p_x_scalar, align 4
%val2 = load i32, ptr %p_y_scalar, align 4
%sum  = add i32 %val1, %val2

  ret void
}
