// loop-transforms.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only loop-transforms.c

/* loop-transforms.c
 *
 * The before-and-after pairs the transformation chapter uses: a loop before and after
 * unrolling, and a multiply inside a loop before and after strength reduction. Each is
 * printed as a bare loop with undeclared names, which is the only reason none of them
 * compiles as it stands.
 *
 * They are kept together because each pair only means anything read against the other,
 * and both pairs need the same declarations.
 */
#define N 1024

int array[N];

/* Before unrolling: one add per iteration, and a branch each time round. */
int unroll_before(int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

/* After unrolling by four. The cleanup loop is not optional. */
int unroll_after(int n) {
    int i, sum = 0;
    for (i = 0; i + 3 < n; i += 4) {
        sum += array[i] + array[i+1] + array[i+2] + array[i+3];
    }
    // Cleanup loop for the last n % 4 elements. The unroller always emits one
    // unless it can prove the trip count is a multiple of the unroll factor;
    // without it, the unrolled loop reads past the end of the array.
    for (; i < n; i++) {
        sum += array[i];

    }
    return sum;
}

/* Before strength reduction: a multiply and a subtract every iteration. */
int strength_before(void) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int j = i * 3 - 2;  // Multiplication and subtraction are performed on each iteration
        sum += j;
    }
    return sum;
}

/* After: the multiply becomes a running addition. */
int strength_after(void) {
    int sum = 0;
    int j = -2;  // when i == 0, j = 0 * 3 - 2 = -2
    for (int i = 0; i < N; i++) {
        sum += j;
        j += 3;  // Instead of recalculating, add 3 to j on each iteration
    }
    return sum;
}
