// pre-common.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only pre-common.c

/* pre-common.c
 *
 * Partial redundancy elimination shown in C: the expression is computed once, before
 * the branch, and both arms use the value. The book prints the if/else with no
 * declarations for t, a, b, cond or use(), which is the only thing stopping it from
 * compiling.
 *
 * The "before" half of this pair is not here. As printed it contains `... use t ...`,
 * an ellipsis standing in for unspecified statements, so it is pseudo-code rather
 * than C and there is no file it could be an excerpt of.
 */
void use(int);

void pre_after(int cond, int a, int b) {
    int t;

    t = a + b;           // inserted on a common ancestor block of both branches
    if (cond) {
        use(t);
    } else {
        use(t);
    }
}
