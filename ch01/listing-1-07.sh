# Listing 1-7. IR generation: the .ll Clang emits
# Run: bash listing-1-07.sh

clang -S -emit-llvm llvm-demo.c -o llvm-demo.ll
# output:
# ; ModuleID = 'llvm-demo.c'
# source_filename = "llvm-demo.c"
# target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
# target triple = "x86_64-unknown-linux-gnu"

# @.str = private unnamed_addr constant [33 x i8] c"Welcome to the LLVM universe!!!\0A\00", align 1

# ; Function Attrs: noinline nounwind optnone uwtable
# define dso_local i32 @main() #0 {
#   %1 = alloca i32, align 4
#   store i32 0, ptr %1, align 4
#   %2 = call i32 (ptr, ...) @printf(ptr noundef @.str)
#   ret i32 0
# }
