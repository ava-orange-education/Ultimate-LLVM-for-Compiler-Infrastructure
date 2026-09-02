// branch-assignment.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only branch-assignment.c

/* branch-assignment.c
 *
 * The C that motivates SSA and phi nodes: x is assigned on both arms of a branch, so
 * after the join there is no single assignment that reaches the use. The book prints
 * only the if/else, because that is the whole point -- but a fragment with undeclared
 * names cannot be compiled, and an example about what the compiler sees should be
 * something the compiler can actually read.
 */
int select_value(int condition, int a, int b) {
    int x;

    if (condition) {
        x = a;
    } else {
        x = b;
    }
    // Use x here
    return x;
}
