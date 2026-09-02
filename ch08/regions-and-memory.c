// regions-and-memory.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only regions-and-memory.c

/* regions-and-memory.c
 *
 * Three examples the chapter prints separately: two stores that MemorySSA has to
 * order across a join, a branch that forms two single-entry single-exit regions, and
 * a loop treated as one region. They share a file because they share the same missing
 * pieces -- declarations for the functions they call and the variables they touch.
 */
void doPositive(void);
void doNonPositive(void);
void finalize(void);
int compute(int);

int A;
int x;
int value1, value2;

/* Two definitions of A reach the load, one per branch. MemorySSA names the merge. */
void two_stores(int cond) {
    if (cond) {
        // In the 'then' branch
        A = value1;   // Store to memory A
    } else {
        // In the 'else' branch
        A = value2;   // Store to memory A
    }
    // Merge point:
    x = A;          // Load from memory A
}

/* Each arm is a region: one entry edge, one exit edge. */
void example(int x) {
    if (x > 0) {
        // Region A: "then" branch
        doPositive();
    } else {
        // Region B: "else" branch
        doNonPositive();
    }
    // Merge point
    finalize();
}

/* A natural loop is a region too, which is why RegionInfo and LoopInfo often agree. */
void processArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = compute(a[i]);
    }
}
