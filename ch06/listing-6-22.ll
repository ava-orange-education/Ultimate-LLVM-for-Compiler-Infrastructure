; Listing 6-22. Declaring a function defined elsewhere
; Run: opt -passes=verify -S listing-6-22.ll -o /dev/null

declare i32 @external_function(i32)
