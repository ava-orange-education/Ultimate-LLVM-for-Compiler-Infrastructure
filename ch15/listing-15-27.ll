; Listing 15-27. Emitting allocas that mem2reg can promote
; Run: opt -passes=verify -S listing-15-27.ll -o /dev/null

define void @example() {
entry:
; GOOD: Use allocas for easy SSA conversion
%x = alloca i32
store i32 1, ptr %x
%val = load i32, ptr %x

; GOOD: Study Clang's CodeGen output
; Write C code and see what Clang emits - this gives best optimization patterns

  ret void
}
