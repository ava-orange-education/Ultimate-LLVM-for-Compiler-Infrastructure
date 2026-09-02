; Listing 10-2. The same loop, tagged with metadata
; Run: opt -passes=verify -S listing-10-02.ll -o /dev/null

define void @copy_forever(ptr %ptr, ptr %ptr2) {
entry:
  br label %loop

loop:
  %x = load i32, ptr %ptr
  store i32 %x, ptr %ptr2
  ; Loop metadata attaches to the back-edge branch. It is not an instruction and
  ; cannot stand on a line of its own.
  br label %loop, !llvm.loop !0
}

; The outer node must be distinct and must name itself as its first operand --
; that self-reference is what gives the loop a stable identity across passes.
!0 = distinct !{!0, !1}
!1 = !{!"has_side_effects"}
