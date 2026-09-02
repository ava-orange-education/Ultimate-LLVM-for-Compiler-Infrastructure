; Listing 6-36. Computing an address with getelementptr
; Run: opt -passes=verify -S listing-6-36.ll -o /dev/null

define void @example(ptr %array) {
entry:
%ptr = getelementptr i32, ptr %array, i32 5

  ret void
}
