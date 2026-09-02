# Listing 13-17. Building IR from Python
# Run: python3 -m py_compile listing-13-17.py

from mlir import ir
with ir.Context(), ir.Location.unknown():
  f32 = ir.F32Type.get()
  const = ir.Operation.create("arith.constant", results=[f32], attributes={"value": ...})
