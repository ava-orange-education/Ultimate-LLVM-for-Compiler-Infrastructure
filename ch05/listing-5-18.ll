; Listing 5-18. Attaching debug metadata to an instruction
; Run: opt -passes=verify -S listing-5-18.ll -o /dev/null

; Attaching debug metadata to an instruction. !dbg names a DILocation, and a
; DILocation needs a scope, so the surrounding subprogram and compile unit are
; part of the example: metadata definitions live at module level, never inside
; a function body.
define i32 @annotated() !dbg !1 {
entry:
  %val = add i32 1, 2, !dbg !0
  ret i32 %val
}

!llvm.dbg.cu = !{!3}
!llvm.module.flags = !{!6}

!0 = !DILocation(line: 10, column: 5, scope: !1)
!1 = distinct !DISubprogram(name: "annotated", scope: !2, file: !2, line: 9,
                            type: !4, spFlags: DISPFlagDefinition, unit: !3)
!2 = !DIFile(filename: "example.c", directory: "/tmp")
!3 = distinct !DICompileUnit(language: DW_LANG_C99, file: !2, producer: "the book",
                             isOptimized: false, runtimeVersion: 0,
                             emissionKind: FullDebug)
!4 = !DISubroutineType(types: !5)
!5 = !{}
!6 = !{i32 2, !"Debug Info Version", i32 3}
