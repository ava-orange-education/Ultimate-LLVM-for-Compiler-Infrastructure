; pre-before.ll -- the complete file.
; Run: opt -passes=verify -S pre-before.ll -o /dev/null

; Partial redundancy elimination, before: a+b is computed on the if.then path and then
; again at the merge, because the if.else path never computed it.
;
; The book prints the block structure as comments (`; Basic Block: Entry`) with the
; instructions under them. Real labels and a function around them are supplied here so
; the file assembles; the printed instructions are unchanged.
define i32 @pre_before(i32 %a, i32 %b, i1 %cond) {
; Assume %a, %b, and %cond are available.
; Basic Block: Entry
entry:
   br i1 %cond, label %if.then, label %if.else

; Basic Block: if.then
if.then:
   %t1 = add i32 %a, %b    ; computation of a+b
   ; ... additional computations using %t1 ...
   br label %merge

; Basic Block: if.else
if.else:
   ; no computation of a+b here
   br label %merge

; Basic Block: merge
merge:
   ; The merge needs a+b whichever way control arrived, and only one path has it,
   ; so the value has to be computed again here. That is the partial redundancy.
   %t = add i32 %a, %b
   %result = mul i32 %t, 2
   ret i32 %result
}
