; Listing 5-11. Hello, World! from Python, lowered to IR
; Run: opt -passes=verify -S listing-5-11.ll -o /dev/null

@.str = private unnamed_addr constant [15 x i8] c"Hello, World!\0A\00"
define void @main() {
entry:
  call void @print_string(ptr getelementptr inbounds ([15 x i8], ptr @.str, i32 0, i32 0))
  ret void
}
declare void @print_string(ptr)
