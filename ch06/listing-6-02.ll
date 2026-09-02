; Listing 6-2. A local, allocated on the stack
; Run: opt -passes=verify -S listing-6-02.ll -o /dev/null

define void @example() {
entry:
%local_var = alloca i32, align 4
store i32 10, ptr %local_var

  ret void
}
