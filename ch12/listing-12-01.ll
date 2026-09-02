; Listing 12-1. A module to compile with llc
; Run: opt -passes=verify -S listing-12-01.ll -o /dev/null

define i32 @main() {
  ret i32 42
}
