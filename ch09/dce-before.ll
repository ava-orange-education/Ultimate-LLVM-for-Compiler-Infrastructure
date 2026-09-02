; dce-before.ll -- the complete file.
; Run: opt -passes=verify -S dce-before.ll -o /dev/null

; What dead-code and dead-store elimination have to work with: a call whose result is
; never used, two stores to the same address with nothing in between, and a load that
; can only ever see the second one.
;
; The book prints the instructions alone. The function around them, the declaration of
; the callee, and the operands they read are what make it a module that assembles.
declare i32 @expensiveComputation()

define i32 @dce_before(ptr %memory, i32 %oldValue, i32 %newValue) {
entry:
; Unused function call
%unused = call i32 @expensiveComputation()
; Two consecutive stores to the same memory location
store i32 %oldValue, ptr %memory    ; (Store #1)
store i32 %newValue, ptr %memory    ; (Store #2)
; A load that uses the most recent value
%final = load i32, ptr %memory
  ret i32 %final
}
