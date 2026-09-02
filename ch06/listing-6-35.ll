; Listing 6-35. A string attribute of your own on a parameter
; Run: opt -passes=verify -S listing-6-35.ll -o /dev/null

define void @custom_function(i32 "custom-attr"="fast-path" %arg) {
entry:
    ret void
}
