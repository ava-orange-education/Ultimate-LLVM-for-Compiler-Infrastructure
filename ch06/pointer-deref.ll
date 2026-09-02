; pointer-deref.ll -- the complete file.
; Run: opt -passes=verify -S pointer-deref.ll -o /dev/null

; Referencing and dereferencing in IR: take the address of x into ptr, load it back,
; and store through it. This is already a complete function in the book -- what keeps
; it from assembling is only that two lines of explanation follow it inside the same
; code block.
define void @example() {
entry:
    %x = alloca i32, align 4       ; Allocate memory for integer x
    store i32 42, ptr %x           ; Initialize x with 42
    %ptr = alloca ptr, align 8     ; Allocate memory for pointer ptr
    store ptr %x, ptr %ptr         ; Store address of x in ptr (Referencing)
    %loaded_ptr = load ptr, ptr %ptr  ; Load stored pointer value
    store i32 10, ptr %loaded_ptr     ; Dereference and modify x to 10
    ret void
}
