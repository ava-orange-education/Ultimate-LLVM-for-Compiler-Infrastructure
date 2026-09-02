; Listing 6-42. Inserting one element into a vector
; Run: opt -passes=verify -S listing-6-42.ll -o /dev/null

define <4 x i32> @vector_insert(<4 x i32> %v, i32 %val) {
entry:
    %newvec = insertelement <4 x i32> %v, i32 %val, i32 1  ; Inserts %val at index 1
    ret <4 x i32> %newvec
}
