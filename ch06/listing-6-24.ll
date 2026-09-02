; Listing 6-24. Calling a variadic function
; Run: opt -passes=verify -S listing-6-24.ll -o /dev/null

declare i32 @printf(ptr, ...)  ; Declare printf

; The string is module-level data: `global` is not an instruction and cannot
; appear inside a function body. "Result: %d\0A\00" is twelve bytes, not thirteen.
@format = private unnamed_addr constant [12 x i8] c"Result: %d\0A\00"

define void @print_example() {
entry:
    %ptr = getelementptr [12 x i8], ptr @format, i32 0, i32 0
    call i32 @printf(ptr %ptr, i32 42)
    ret void
}
