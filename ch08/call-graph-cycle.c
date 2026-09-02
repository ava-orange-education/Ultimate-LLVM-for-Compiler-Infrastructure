// call-graph-cycle.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only call-graph-cycle.c

/* call-graph-cycle.c
 *
 * The call graph the chapter walks through: A, B and C form a cycle, D stands apart,
 * and main reaches both. This is already a complete program in the book -- it is kept
 * here so the excerpt has something to be an excerpt of, and so the reader has a file
 * that compiles and can actually be fed to opt -passes=print<call-graph>.
 */
void A(void);
void B(void);
void C(void);
void D(void);

void A() { B(); }
void B() { C(); }
void C() { A(); }
void D() { }  // an independent function

int main() {
    A();  // Calls the recursive cycle A-B-C.
    D();  // Also calls function D.
}
