; Listing 5-13. A module: one global and one function
; Run: opt -passes=verify -S listing-5-13.ll -o /dev/null

; Module containing a single function and global variable
@globalVar = global i32 42

define i32 @main() {
entry:
  ret i32 0
}
