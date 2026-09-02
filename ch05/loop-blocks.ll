; loop-blocks.ll -- the complete file.
; Run: opt -passes=verify -S loop-blocks.ll -o /dev/null

; A counted loop expressed as basic blocks and branches, with a phi carrying the
; induction variable. The book prints the blocks without a function header, which is
; the only thing separating it from a module that assembles.
define void @loop_example() {
entry:
  br label %loop
loop:
  %i = phi i32 [0, %entry], [%next_i, %body]
  %cond = icmp slt i32 %i, 10
  br i1 %cond, label %body, label %exit
body:
  %next_i = add i32 %i, 1
  br label %loop
exit:
  ret void
}
