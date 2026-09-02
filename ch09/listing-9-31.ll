; Listing 9-31. The same function in IR, before the tail call is turned into a loop
; Run: opt -passes=verify -S listing-9-31.ll -o /dev/null

define i32 @factorial_tail(i32 %n, i32 %acc) {
entry:
  %cmp = icmp eq i32 %n, 0
  br i1 %cmp, label %return, label %recurse

return:
  ret i32 %acc

recurse:
  %n_dec = sub i32 %n, 1
  %acc_new = mul i32 %n, %acc
  ; A tail call is marked to indicate eligibility for TCO
  %call = tail call i32 @factorial_tail(i32 %n_dec, i32 %acc_new)

  ret i32 %call  ; the tail call's result must be returned for TCO to apply

}
