// macro-expansion.c -- the complete file.
// Run: clang++ -I$LLVM_DIR/include -std=c++17 -fsyntax-only macro-expansion.c

/* macro-expansion.c
 *
 * What the preprocessor sees and what it hands to the parser. The chapter prints the
 * macro and its use twice -- once as source, once after expansion -- to show that PI
 * is gone by the time the compiler proper runs. Both are two loose lines with an
 * undeclared r, so neither can be compiled as printed; this is the file they belong
 * to, and it can be run through `clang -E` to show the expansion for real.
 */
#define PI 3.14

double circle_area_double(double r) {
    double area = PI * r * r;
    return area;
}

float circle_area_float(float r) {
    float area = PI * r * r;
    return area;
}
