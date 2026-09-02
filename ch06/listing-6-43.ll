; Listing 6-43. Shuffling elements between two vectors
; Run: opt -passes=verify -S listing-6-43.ll -o /dev/null

define <4 x i32> @vector_shuffle(<4 x i32> %v1, <4 x i32> %v2) {
entry:
    ; Create a shuffled vector with selected elements from %v1 and %v2.
    ; For instance, <i32 0, i32 5, i32 1, i32 7> takes the 0th and 1st elements from %v1, 
    ; and the 1st and 3rd elements (offset by 4) from %v2.
    %shuffled = shufflevector <4 x i32> %v1, <4 x i32> %v2, <4 x i32> <i32 0, i32 5, i32 1, i32 7>
    ret <4 x i32> %shuffled
}
