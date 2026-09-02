# Listing 1-20. Analysing and dumping the AST with clang-check
# Run: bash listing-1-20.sh

clang-check --analyze clang-check-demo.cpp --

# clang-check-demo.cpp:3:2: warning: Undefined or garbage value returned to caller [core.uninitialized.UndefReturn]

# 3 |         return ptr;

#   |         ^~~~~~~~~~

clang-check --ast-print clang-check-demo.cpp --

# TranslationUnitDecl 0x6286a71eb9c8 <<invalid sloc>> <invalid sloc>

# |-TypedefDecl 0x6286a71ec238 <<invalid sloc>> <invalid sloc> implicit __int128_t '__int128'

# | `-BuiltinType 0x6286a71ebf90 '__int128'

# |-TypedefDecl 0x6286a71ec2a8 <<invalid sloc>> <invalid sloc> implicit __uint128_t 'unsigned __int128'

# | `-BuiltinType 0x6286a71ebfb0 'unsigned __int128'

# |-TypedefDecl 0x6286a71ec620 <<invalid sloc>> <invalid sloc> implicit __NSConstantString '__NSConstantString_tag'

# | `-RecordType 0x6286a71ec390 '__NSConstantString_tag'

# |   `-CXXRecord 0x6286a71ec300 '__NSConstantString_tag'

# |-TypedefDecl 0x6286a71ec6c8 <<invalid sloc>> <invalid sloc> implicit __builtin_ms_va_list 'char *'

# | `-PointerType 0x6286a71ec680 'char *'

# |   `-BuiltinType 0x6286a71eba70 'char'

# |-TypedefDecl 0x6286a7235220 <<invalid sloc>> <invalid sloc> implicit __builtin_va_list '__va_list_tag[1]'

# | `-ConstantArrayType 0x6286a72351c0 '__va_list_tag[1]' 1

# |   `-RecordType 0x6286a71ec7b0 '__va_list_tag'

# |     `-CXXRecord 0x6286a71ec720 '__va_list_tag'

# |-FunctionDecl 0x6286a7235308 </home/hemantab/workspace/sf_llvm/Chapters/Chapter_1/clang-check-demo.cpp:1:1, line:4:1> line:1:6 used getPtr 'int *()'

# | `-CompoundStmt 0x6286a72354d8 <col:15, line:4:1>

# |   |-DeclStmt 0x6286a7235478 <line:2:2, col:10>

# |   | `-VarDecl 0x6286a7235410 <col:2, col:7> col:7 used ptr 'int *'

# |   `-ReturnStmt 0x6286a72354c8 <line:3:2, col:9>

# |     `-ImplicitCastExpr 0x6286a72354b0 <col:9> 'int *' <LValueToRValue>

# |       `-DeclRefExpr 0x6286a7235490 <col:9> 'int *' lvalue Var 0x6286a7235410 'ptr' 'int *'

# `-FunctionDecl 0x6286a7235558 <line:7:1, line:10:1> line:7:5 main 'int ()'

#   `-CompoundStmt 0x6286a72357d0 <col:12, line:10:1>

#     |-DeclStmt 0x6286a7235788 <line:8:2, col:21>

#     | `-VarDecl 0x6286a7235648 <col:2, col:20> col:7 ptr 'int *' cinit

#     |   `-CallExpr 0x6286a7235768 <col:13, col:20> 'int *'

#     |     `-ImplicitCastExpr 0x6286a7235750 <col:13> 'int *(*)()' <FunctionToPointerDecay>

#     |       `-DeclRefExpr 0x6286a72356f8 <col:13> 'int *()' lvalue Function 0x6286a7235308 'getPtr' 'int *()'

#     `-ReturnStmt 0x6286a72357c0 <line:9:2, col:9>

#       `-IntegerLiteral 0x6286a72357a0 <col:9> 'int' 0
