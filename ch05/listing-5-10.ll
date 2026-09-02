; Listing 5-10. The same program as IR
; Run: opt -passes=verify -S listing-5-10.ll -o /dev/null

; "Hello, World!\0A\00" is fifteen bytes: thirteen characters, a newline and a NUL.
@.str = private unnamed_addr constant [15 x i8] c"Hello, World!\0A\00"
define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr getelementptr inbounds ([15 x i8], ptr @.str, i32 0, i32 0))
  ret i32 0
}
declare i32 @printf(ptr, ...)
