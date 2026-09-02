; Listing 15-4. A FileCheck test that pins what the pass emits
; Run: opt -passes=verify -S listing-15-04.ll -o /dev/null

; Test file (test.ll)
; RUN: opt -passes=instcombine %s -S | FileCheck %s

define i32 @add_constants() {
entry:
  ; CHECK-LABEL: @add_constants
  ; CHECK-NOT: add i32 5, 3
  ; CHECK: ret i32 8
  %result = add i32 5, 3
  ret i32 %result
}
