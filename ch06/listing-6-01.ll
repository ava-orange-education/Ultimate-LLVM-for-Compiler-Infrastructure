; Listing 6-1. A global variable
; Run: opt -passes=verify -S listing-6-01.ll -o /dev/null

@global_var = global i32 42, align 4
