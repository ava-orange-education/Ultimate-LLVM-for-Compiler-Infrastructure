; Listing 10-11. A loop for the pass to tag
; Run: opt -passes=verify -S listing-10-11.ll -o /dev/null

define void @count(i32 %userInput) {
entry:
  %i = alloca i32, align 4
  %userInput.addr = alloca i32, align 4
  store i32 0, ptr %i, align 4
  store i32 %userInput, ptr %userInput.addr, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %userInput.addr, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end, !llvm.loop !0

for.body:                                         ; preds = %for.cond
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %2 = load i32, ptr %i, align 4
  %inc = add nsw i32 %2, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

; The distinct outer node references itself first, then its hints.
!0 = distinct !{!0, !1}
!1 = !{!"loop.has.sideeffects"}
