; Listing 6-41. Extracting one element from a vector
; Run: opt -passes=verify -S listing-6-41.ll -o /dev/null

define i32 @vector_extract(<4 x i32> %v) {
entry:
    %elem = extractelement <4 x i32> %v, i32 2  ; Extracts the element at index 2
    ret i32 %elem
}
