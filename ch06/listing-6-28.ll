; Listing 6-28. Internal linkage: private to the module
; Run: opt -passes=verify -S listing-6-28.ll -o /dev/null

define internal i32 @helper_function(i32 %x) {
    %result = mul i32 %x, 2
    ret i32 %result
}
