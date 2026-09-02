; phi-and-hoist.ll -- the complete file.
; Run: opt -passes=verify -S phi-and-hoist.ll -o /dev/null

; Two IR fragments from the pass chapter: the phi that merges a value assigned on both
; arms of a branch, and the loop-body load that a hoist would move to the preheader.
; Both are printed as loose instructions -- the phi without the blocks it names, the
; load without the loop it sits in -- so neither assembles as it stands.
define i32 @merge(i1 %cond) {
entry:
  br i1 %cond, label %then, label %else
then:
  br label %merge
else:
  br label %merge
merge:
  %x = phi i32 [10, %then], [20, %else]
  ret i32 %x
}

define void @hoistable(ptr %ptr, i1 %cond) {
entry:
  br label %loop
loop:
  %a = load i32, ptr %ptr
  %b = add i32 %a, 1
  br i1 %cond, label %loop, label %exit
exit:
  ret void
}
