; Listing 6-45. Attaching custom metadata to an instruction
; Run: opt -passes=verify -S listing-6-45.ll -o /dev/null

; Define a function that uses custom metadata
define i32 @main() {
entry:
    %ptr = alloca i32, align 4
    ; Store the value 10 into the allocated memory and attach custom metadata
    store i32 10, ptr %ptr, align 4, !custom_md !4
    ret i32 0
}
; A metadata string has to be wrapped in a node: `!0 = !"..."` is not a
; definition on its own.
!0 = !{!"Custom Info"}
; A metadata node that groups the metadata string with an integer value
!4 = !{!0, i32 100}

; Named metadata to group custom metadata nodes (optional)
!my.custom.metadata = !{!4}
