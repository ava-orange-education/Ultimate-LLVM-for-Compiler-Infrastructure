# Listing 13-46. The same construction from Python
# Run: python3 -m py_compile listing-13-46.py

from mlir import ir
with ir.Context(), ir.Location.unknown():
    module = ir.Module.create()
    f32 = ir.F32Type.get()
    const_val = ir.FloatAttr.get(f32, 3.14)

    with ir.InsertionPoint(module.body):
        op = ir.Operation.create("arith.constant",
                                 attributes={"value": const_val},
                                 results=[f32])
