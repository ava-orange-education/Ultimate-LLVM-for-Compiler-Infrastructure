; Listing 6-11. The bitwise and logical operations
; Run: opt -passes=verify -S listing-6-11.ll -o /dev/null

define void @logical_operations(i32 %a, i32 %b) {
    ; Bitwise AND
    %and_result = and i32 %a, %b
    ; Bitwise OR
    %or_result = or i32 %a, %b
    ; Bitwise XOR
    %xor_result = xor i32 %a, %b
    ; Logical NOT (using XOR with -1)
    %not_result = xor i32 %a, -1
    ; Integer Comparison (Equality Check)
    %is_equal = icmp eq i32 %a, %b
    ; Integer Comparison (Less Than)
    %is_less = icmp slt i32 %a, %b
    ; Floating-Point Comparison (Greater Than)
    %fa = sitofp i32 %a to float
    %fb = sitofp i32 %b to float
    %is_greater = fcmp ogt float %fa, %fb
    ret void
}
