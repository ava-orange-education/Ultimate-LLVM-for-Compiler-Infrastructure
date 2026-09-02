; Listing 6-34. A string attribute that sets an AMD GPU work group size
; Run: opt -passes=verify -S listing-6-34.ll -o /dev/null

define void @example(i32 "amdgpu-flat-work-group-size"="1,256" %x) {
entry:
    ret void
}
