; Listing 9-3. A value computed and never used
; Run: opt -passes=verify -S listing-9-03.ll -o /dev/null

define void @example(i32 %a) {
entry:
%temp = add i32 %a, 0    ; %temp is computed but never used

  ret void
}
