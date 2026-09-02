# Listing 1-5. Parsing: the abstract syntax tree
# Run: bash listing-1-05.sh

clang -Xclang -ast-dump -fsyntax-only llvm-demo.c
# output:
# …
# `-FunctionDecl 0x5b0c8c7d7328 <llvm-demo.c:3:1, line:6:1> line:3:5 main 'int ()'
#   `-CompoundStmt 0x5b0c8c7d7540 <col:12, line:6:1>
#     |-CallExpr 0x5b0c8c7d74b8 <line:4:5, col:47> 'int'
#     | |-ImplicitCastExpr 0x5b0c8c7d74a0 <col:5> 'int (*)(const char *, ...)' <FunctionToPointerDecay>
#     | | `-DeclRefExpr 0x5b0c8c7d73d0 <col:5> 'int (const char *, ...)' Function 0x5b0c8c79a0b8 'printf' 'int (const char *, ...)'
#     | `-ImplicitCastExpr 0x5b0c8c7d74f8 <col:12> 'const char *' <NoOp>
#     |   `-ImplicitCastExpr 0x5b0c8c7d74e0 <col:12> 'char *' <ArrayToPointerDecay>
#     |     `-StringLiteral 0x5b0c8c7d7420 <col:12> 'char[33]' lvalue "Welcome to the LLVM universe!!!\n"
#     `-ReturnStmt 0x5b0c8c7d7530 <line:5:5, col:12>
#       `-IntegerLiteral 0x5b0c8c7d7510 <col:12> 'int' 0
