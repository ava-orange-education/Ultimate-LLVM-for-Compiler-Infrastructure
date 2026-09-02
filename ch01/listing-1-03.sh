# Listing 1-3. Preprocessing: what -E produces
# Run: bash listing-1-03.sh

clang -E llvm-demo.c
# output:
# # 1 "llvm-demo.c"
# # 1 "<built-in>" 1
# # 1 "<built-in>" 3
# # 400 "<built-in>" 3
# # 1 "<command line>" 1
# # 1 "<built-in>" 2
# # 1 "llvm-demo.c" 2
# # 1 "/usr/include/stdio.h" 1 3 4
# # 28 "/usr/include/stdio.h" 3 4
# # 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# # 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
# …
# # 959 "/usr/include/stdio.h" 3 4
# extern int __uflow (FILE *);
# extern int __overflow (FILE *, int);
# # 2 "llvm-demo.c" 2

# int main() {
#     printf("Welcome to the LLVM universe!!!\n");
#     return 0;
# }
