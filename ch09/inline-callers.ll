; inline-callers.ll -- the complete file.
; Run: opt -passes=verify -S inline-callers.ll -o /dev/null

; The two callers the inlining section works through: one calling a straight-line
; callee, one calling a callee that branches. The book prints each caller on its own,
; so in both cases the function being called is undeclared and the module will not
; assemble. Both callees are given here, with bodies, because whether inlining is
; profitable is a statement about what is on the other side of the call.
define i32 @add(i32 %a, i32 %b) {
  %sum = add i32 %a, %b
  ret i32 %sum
}

define i32 @max(i32 %a, i32 %b) {
  %cmp = icmp sgt i32 %a, %b
  br i1 %cmp, label %ret.a, label %ret.b
ret.a:
  ret i32 %a
ret.b:
  ret i32 %b
}

define i32 @computeSum(i32 %x, i32 %y) {
  %result = call i32 @add(i32 %x, i32 %y)
  ret i32 %result
}

define i32 @computeMax(i32 %x, i32 %y) {
  %result = call i32 @max(i32 %x, i32 %y)
  ret i32 %result
}
