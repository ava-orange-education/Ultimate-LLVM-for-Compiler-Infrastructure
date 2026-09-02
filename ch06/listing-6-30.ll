; Listing 6-30. An attribute group, defined once and referenced
; Run: opt -passes=verify -S listing-6-30.ll -o /dev/null

define i32 @example(i32 %x) #0 {
    ret i32 %x
}
attributes #0 = { alwaysinline noreturn }
