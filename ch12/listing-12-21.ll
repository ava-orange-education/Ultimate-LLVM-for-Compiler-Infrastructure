; Listing 12-21. A load the DAG combiner can fold
; Run: opt -passes=verify -S listing-12-21.ll -o /dev/null

define void @example(ptr %addr) {
entry:
%val = load i32, ptr %addr
%sum = add i32 %val, 8

  ret void
}
