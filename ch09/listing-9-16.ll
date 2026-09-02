; Listing 9-16. A callee with a branch, marked alwaysinline
; Run: opt -passes=verify -S listing-9-16.ll -o /dev/null

define i32 @max(i32 %a, i32 %b) alwaysinline {
  %cond = icmp sgt i32 %a, %b
  %result = select i1 %cond, i32 %a, i32 %b
  ret i32 %result
}
