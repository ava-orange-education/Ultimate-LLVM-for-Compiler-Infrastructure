; Listing 9-18. After inlining: the body substituted in place
; Run: opt -passes=verify -S listing-9-18.ll -o /dev/null

define i32 @example(i32 %x, i32 %y) {
entry:
%cond = icmp sgt i32 %x, %y
%result = select i1 %cond, i32 %x, i32 %y
ret i32 %result

}
