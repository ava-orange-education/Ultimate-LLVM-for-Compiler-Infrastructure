; Listing 9-38. In IR: computed once, before the branch

; Basic Block: Entry - Insert the computation early:
   %t_common = add i32 %a, %b   ; Compute a+b once at the common ancestor.
   br i1 %cond, label %if.then, label %if.else

; Basic Block: if.then
   ; Instead of recomputing, use %t_common
   ; ... additional computations using %t_common ...
   br label %merge

; Basic Block: if.else
   ; No need to recompute, %t_common is already computed in Entry.
   br label %merge

; Basic Block: merge
   ; No phi is needed. %t_common is computed in entry, which dominates this block,
   ; so it can be named directly; a phi whose incoming values are all the same value
   ; is degenerate and is folded away as soon as anything looks at it.

   %result = mul i32 %t_common, 2

   ret i32 %result
