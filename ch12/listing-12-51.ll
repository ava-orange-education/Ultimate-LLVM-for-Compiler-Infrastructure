; Listing 12-51. A lit test with FileCheck assertions
; Run: opt -passes=verify -S listing-12-51.ll -o /dev/null

; RUN: llc -march=myarch < %s | FileCheck %s
define i32 @add(i32 %a, i32 %b) {
  ; CHECK: add GPR32, GPR32
  %sum = add i32 %a, %b
  ret i32 %sum
}
