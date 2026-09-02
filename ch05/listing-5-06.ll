; Listing 5-6. The two branches, each defining its own name
; Run: opt -passes=verify -S listing-5-06.ll -o /dev/null

define void @example(i32 %a, i32 %b) {
; Block for 'then' branch
then:
  %x1 = add i32 %a, 0  ; Assign %x1 in the 'then' branch
  br label %merge      ; Branch to merge block
; Block for 'else' branch
else:
  %x2 = add i32 %b, 0  ; Assign %x2 in the 'else' branch
  br label %merge      ; Branch to merge block
; Merge block
merge:
  %x = phi i32 [ %x1, %then ], [ %x2, %else ] ; Select based on predecessor

  ret void
}
