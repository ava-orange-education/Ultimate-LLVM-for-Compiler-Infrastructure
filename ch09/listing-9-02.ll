; Listing 9-2. A multiply by one and a subtract of zero
; Run: opt -passes=verify -S listing-9-02.ll -o /dev/null

define void @example(i32 %a) {
entry:
; Original IR snippet
%tmp = mul i32 %a, 1
%final = sub i32 %tmp, 0

  ret void
}
