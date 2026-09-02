; vector-type.ll -- the complete file.
; Run: opt -passes=verify -S vector-type.ll -o /dev/null

; A named vector type. The listing is tagged as C++ in the title table but this is
; LLVM assembly -- the leading semicolon comment and the `type` keyword only parse as
; .ll -- so it is checked with llvm-as, not clang++.
;
; A type definition alone is a module that assembles but does nothing; a use is given
; so the type is not dead and the reader can see what it is for.

; Definition of a vector of four 32-bit integers
%vec = type <4 x i32>

define %vec @vector_add(%vec %a, %vec %b) {
  %sum = add <4 x i32> %a, %b
  ret %vec %sum
}
