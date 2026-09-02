# Listing 12-2. Compiling IR to assembly with llc
# Run: bash listing-12-02.sh

llc main.ll -o main.s       # Emit assembly
llc main.ll -filetype=obj   # Emit object code
