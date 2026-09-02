; Listing 9-5. After: only the live store remains
; Run: opt -passes=verify -S listing-9-05.ll -o /dev/null

define void @example(i32 %newValue, ptr %memory) {
entry:
; The call to @expensiveComputation() is removed

; Only the necessary store remains
store i32 %newValue, ptr %memory

; The load fetches the correct, live value
%final = load i32, ptr %memory

  ret void
}
