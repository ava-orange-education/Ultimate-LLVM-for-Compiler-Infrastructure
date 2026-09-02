; Listing 6-19. An expression LLVM folds to a constant
; Run: opt -passes=verify -S listing-6-19.ll -o /dev/null

define i32 @constant_example() {
    %x = add i32 10, 5  ; LLVM simplifies this to 15
    ret i32 %x
}
