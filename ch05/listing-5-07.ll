; Listing 5-7. Constant folding in SSA form
; Run: opt -passes=verify -S listing-5-07.ll -o /dev/null

; In SSA form every assignment introduces a new name. A bare `%x1 = 5` is not an
; instruction: a constant reaches a register through an operation.
;
; The book prints only the three assignments. They are shown here inside the function
; that gives them meaning, because a register sequence on its own is not a module and
; will not assemble -- llvm-as needs somewhere for the values to live.
define i32 @ssa_example() {
entry:
%x1 = add i32 0, 5
%x2 = add i32 %x1, 3
%y1 = add i32 %x2, 2
  ret i32 %y1
}
