; call-and-byval.ll -- the complete file.
; Run: opt -passes=verify -S call-and-byval.ll -o /dev/null

; Two of the assembly-language chapter's examples: an ordinary call, and a struct
; passed byval. Both are printed without the declarations they depend on -- @add in
; the first, and nothing at all defines the caller's callee -- so neither assembles as
; printed.
%struct.Data = type { i32, float }

define i32 @add(i32 %a, i32 %b) {
entry:
    %sum = add i32 %a, %b
    ret i32 %sum
}

define i32 @caller(i32 %x, i32 %y) {
entry:
    %result = call i32 @add(i32 %x, i32 %y)
    ret i32 %result
}

; byval copies the struct into the callee's frame, so %arg is a pointer to that copy
; and the getelementptr walks it.
define void @process_data(ptr byval(%struct.Data) %arg) {
entry:
    %field = getelementptr %struct.Data, ptr %arg, i32 0, i32 1
    %val = load float, ptr %field
    ret void
}
