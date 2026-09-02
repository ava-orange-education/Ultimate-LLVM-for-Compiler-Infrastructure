; Listing 12-23. The load and add a compound pattern matches
; Run: opt -passes=verify -S listing-12-23.ll -o /dev/null

define void @example(ptr %base) {
entry:
%val = load i32, ptr %base
%sum = add i32 %val, 8

  ret void
}
