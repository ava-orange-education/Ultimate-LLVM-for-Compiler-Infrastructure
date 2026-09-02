// Listing 9-12. The loop vectorised, in pseudo-IR

; Pseudo-IR for vectorized loop
vector_sum = <0,0,0,0>
for (i = 0; i < n; i += 4) {
    vec = load <4 x i32>, <4 x i32>* (array + i)
    vector_sum = add <4 x i32> (vector_sum, vec)
}
sum = horizontal_add(vector_sum)
