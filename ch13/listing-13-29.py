# Listing 13-29. Prototyping a module in Python
# Run: python3 -m py_compile listing-13-29.py

from mlir import ir
with ir.Context(), ir.Location.unknown():
  f32 = ir.F32Type.get()
  module = ir.Module.create()
  with ir.InsertionPoint(module.body):
    const = ir.Operation.create("arith.constant",
        attributes={"value": ir.FloatAttr.get(f32, 3.14)},
        results=[f32])
