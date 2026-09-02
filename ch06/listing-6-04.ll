; Listing 6-4. An opaque pointer, allocated
; Run: opt -passes=verify -S listing-6-04.ll -o /dev/null

define void @example() {
entry:
%p = alloca ptr, align 8   ; allocates storage for an opaque pointer

  ret void
}
