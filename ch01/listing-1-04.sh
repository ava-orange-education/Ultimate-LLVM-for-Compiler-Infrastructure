# Listing 1-4. Lexing: the token stream
# Run: bash listing-1-04.sh

clang -Xclang -dump-tokens -fsyntax-only llvm-demo.c
# output:
# …
# int 'int'        [StartOfLine]  Loc=<llvm-demo.c:3:1>
# identifier 'main'        [LeadingSpace] Loc=<llvm-demo.c:3:5>
# l_paren '('             Loc=<llvm-demo.c:3:9>
# r_paren ')'             Loc=<llvm-demo.c:3:10>
# l_brace '{'      [LeadingSpace] Loc=<llvm-demo.c:3:12>
# identifier 'printf'      [StartOfLine] [LeadingSpace]   Loc=<llvm-demo.c:4:5>
# l_paren '('             Loc=<llvm-demo.c:4:11>
# string_literal '"Welcome to the LLVM universe!!!\n"'            Loc=<llvm-demo.c:4:12>
# r_paren ')'             Loc=<llvm-demo.c:4:47>
# semi ';'                Loc=<llvm-demo.c:4:48>
# return 'return'  [StartOfLine] [LeadingSpace]   Loc=<llvm-demo.c:5:5>
# numeric_constant '0'     [LeadingSpace] Loc=<llvm-demo.c:5:12>
# semi ';'                Loc=<llvm-demo.c:5:13>
# r_brace '}'      [StartOfLine]  Loc=<llvm-demo.c:6:1>
# eof ''          Loc=<llvm-demo.c:6:2>
