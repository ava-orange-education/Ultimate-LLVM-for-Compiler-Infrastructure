; basic-block-branch.ll -- the complete file.
; Run: opt -passes=verify -S basic-block-branch.ll -o /dev/null

; A basic block ends in exactly one terminator. The book prints the entry block on its
; own to make that shape visible; the block it branches to has to exist for the module
; to assemble, so it is supplied here.
define i32 @block_with_branch(i32 %a, i32 %b) {
entry:
  %sum = add i32 %a, %b    ; Add two integers
  br label %next           ; Unconditional branch to 'next'

next:
  ret i32 %sum
}
