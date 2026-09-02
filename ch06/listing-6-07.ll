; Listing 6-7. Loading and storing through a pointer
; Run: opt -passes=verify -S listing-6-07.ll -o /dev/null

define void @example() {
    %ptr = alloca i32  ; Allocate space for an integer
    store i32 42, ptr %ptr  ; Store value in allocated memory
    %val = load i32, ptr %ptr  ; Load value from memory
    ret void
}
