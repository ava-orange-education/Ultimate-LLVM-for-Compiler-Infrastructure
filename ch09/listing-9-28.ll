; Listing 9-28. The same function with the variable in memory
; Run: opt -passes=verify -S listing-9-28.ll -o /dev/null

define i32 @computeSum(i32 %a, i32 %b) {
entry:
  %x = alloca i32, align 4         ; Allocate space for x on the stack.
  %sum = add i32 %a, %b             ; Compute a + b.
  store i32 %sum, ptr %x, align 4   ; Store the result into memory.
  %val = load i32, ptr %x, align 4  ; Load the result back from memory.
  ret i32 %val                      ; Return the result.
}
