# Listing 1-25. Linking the objects with lld, on Linux and on Windows
# Run: bash listing-1-25.sh

# On Linux

ld.lld -o llvm-demo llvm-demo-opt.o llvm-demo-1-opt.o

# On Windows

lld-link -o llvm-demo.exe llvm-demo-opt.obj llvm-demo-1-opt.obj
