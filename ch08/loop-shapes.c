// loop-shapes.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only loop-shapes.c

/* loop-shapes.c
 *
 * The loops the analysis chapter describes: a plain counted loop, one with a
 * loop-carried dependence, and one whose first iteration is special. Each is printed
 * on its own because each illustrates a different thing for LoopInfo, dependence
 * analysis and trip-count reasoning to say -- but a loop with undeclared N and A is
 * not something a compiler can be pointed at, and these examples are entirely about
 * what the compiler concludes.
 */
void doSpecialCase(void);
void doRegularWork(void);

/* The shape LoopInfo recognises: a preheader, a header with the test, a latch. */
void counted(int N) {
    for (int i = 0; i < N; i++) {
        // loop body
    }
}

/* sum is read and written on every iteration, so iteration i+1 cannot start before
   iteration i has finished. That is the carried dependence. */
void carried(int N, const int *A, int *B) {
    int sum = 0;
    // Original C code:
    for (int i = 0; i < N; i++) {
        sum += A[i];
        B[i] = sum;
    }
}

/* A loop the unroller and the peeler treat differently, because the condition is
   invariant except on the first iteration. */
void first_iteration_differs(int N) {
    for (int i = 0; i < N; i++) {
        if (i == 0)
            doSpecialCase();
        else
            doRegularWork();
    }
}
