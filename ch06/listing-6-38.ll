; Listing 6-38. The same nesting as IR types
; Run: opt -passes=verify -S listing-6-38.ll -o /dev/null

%struct.Inner = type { [3 x i32], float }
%struct.Outer = type { double, %struct.Inner }
define void @example(ptr %ptr) {
entry:
    ; Access ptr->b (Inner struct)
    %b_ptr = getelementptr %struct.Outer, ptr %ptr, i32 0, i32 1
    ; Access ptr->b.values[1] (second element in array)
    %array_ptr = getelementptr %struct.Inner, ptr %b_ptr, i32 0, i32 0
    %element_ptr = getelementptr [3 x i32], ptr %array_ptr, i32 0, i32 1
    ; Store a new value (99) in values[1]

    ret void
}
