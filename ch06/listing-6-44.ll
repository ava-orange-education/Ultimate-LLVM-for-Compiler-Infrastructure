; Listing 6-44. Zeroing a stack slot with the memset intrinsic
; Run: opt -passes=verify -S listing-6-44.ll -o /dev/null

; Zeroing a stack slot with the memset intrinsic.
;
; Overloaded intrinsics carry their operand types in the name. Under opaque pointers
; the pointer part is `p0` -- there is no i8* left to spell -- so the LLVM 18 name
; @llvm.memset.p0i8.i32 no longer exists. The pointer operand was already written
; `ptr`; only the intrinsic name was out of date.
declare void @llvm.memset.p0.i32(ptr, i8, i32, i1)

define void @zero_a_slot() {
entry:
%ptr = alloca i32, align 4
call void @llvm.memset.p0.i32(ptr %ptr, i8 0, i32 4, i1 false)
  ret void
}
