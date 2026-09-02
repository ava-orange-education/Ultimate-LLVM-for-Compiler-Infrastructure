; Listing 5-20. A control-flow graph, with a phi at the merge
; Run: opt -passes=verify -S listing-5-20.ll -o /dev/null

define i32 @choose(i32 %a, i32 %b) {
entry:
  %cond = icmp eq i32 %a, %b
  br i1 %cond, label %then, label %else
then:
  %x.then = add i32 %a, 1
  br label %merge
else:
  %x.else = sub i32 %a, 1
  br label %merge
merge:
  ; SSA allows one definition per name, so the two branches cannot both define
  ; %x. A phi node names the value that arrived, according to the edge taken.
  %x = phi i32 [ %x.then, %then ], [ %x.else, %else ]
  ret i32 %x
}
