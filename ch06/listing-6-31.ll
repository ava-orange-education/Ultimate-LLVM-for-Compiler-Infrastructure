; Listing 6-31. A parameter attribute
; Run: opt -passes=verify -S listing-6-31.ll -o /dev/null

define void @process(ptr nonnull %data) {
entry:
    %val = load i32, ptr %data
    ret void
}
