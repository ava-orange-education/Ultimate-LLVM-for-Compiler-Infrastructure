; Listing 6-32. How a narrow argument is widened
; Run: opt -passes=verify -S listing-6-32.ll -o /dev/null

define i32 @convert(i8 zeroext %x) {
entry:
    %extended = zext i8 %x to i32
    ret i32 %extended
}
