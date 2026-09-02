; three-instructions.ll -- the complete file.
; Run: opt -passes=verify -S three-instructions.ll -o /dev/null

; The three instruction categories the chapter names: arithmetic, memory and control
; flow. The book prints one example of each, one line apiece, which is why they have
; no function around them there -- they are not meant as a program.
;
; They still have to assemble, so here they are in a function that gives every operand
; a definition.
define void @three_kinds(i32 %a, i32 %b, ptr %ptr) {
entry:
%sum = add i32 %a, %b  ; Adds two integers
%val = load i32, ptr %ptr  ; Loads a value from memory
br label %next  ; Branches unconditionally

next:
  %total = add i32 %sum, %val
  store i32 %total, ptr %ptr
  ret void
}
