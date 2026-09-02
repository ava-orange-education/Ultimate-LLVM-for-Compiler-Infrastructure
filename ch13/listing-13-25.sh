# Listing 13-25. Generating C++ from ODS with mlir-tblgen
# Run: bash listing-13-25.sh

mlir-tblgen my_ops.td -gen-op-defs -I path/to/td -o MyOps.cpp
