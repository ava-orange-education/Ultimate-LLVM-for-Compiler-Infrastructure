; Listing 6-40. Adding two vectors elementwise
; Run: opt -passes=verify -S listing-6-40.ll -o /dev/null

define <4 x i32> @vector_add(<4 x i32> %v1, <4 x i32> %v2) {
entry:
    %sum = add <4 x i32> %v1, %v2     ; Elementwise addition
    ret <4 x i32> %sum
}
