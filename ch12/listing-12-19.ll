; Listing 12-19. A load whose address folds into the instruction
; Run: opt -passes=verify -S listing-12-19.ll -o /dev/null

define void @example(ptr %base) {
entry:
%ptr = load i32, ptr %base
%sum = add i32 %ptr, 8

  ret void
}
