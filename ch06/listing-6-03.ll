; Listing 6-3. Unnamed values, numbered in order
; Run: opt -passes=verify -S listing-6-03.ll -o /dev/null

define void @example(i32 %X) {
entry:
%0 = add i32 %X, %X
%1 = add i32 %0, %0
%result = add i32 %1, %1

  ret void
}
