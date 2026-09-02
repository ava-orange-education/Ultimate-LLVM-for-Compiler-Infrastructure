; Listing 8-4. Loads the alias analysis must disambiguate
; Run: opt -passes=verify -S listing-8-04.ll -o /dev/null

define void @example(ptr %p, ptr %q) {
entry:
%1 = load i32, ptr %p
%2 = load i32, ptr %q
%3 = add i32 %1, %2

  ret void
}
