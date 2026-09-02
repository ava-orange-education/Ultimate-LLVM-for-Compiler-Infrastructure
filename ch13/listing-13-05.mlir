// Listing 13-5. A discardable attribute attached to an operation
// Run: mlir-opt --verify-roundtrip listing-13-05.mlir

func.func @attributed(%cond: i1, %A: memref<1xf32>) {
  %c0 = arith.constant 0 : index
  %one = arith.constant 1.0 : f32

  // Any operation can carry discardable attributes, written as a dictionary after
  // its regions. They are metadata: passes may read them and may drop them.
  scf.if %cond {
    memref.store %one, %A[%c0] : memref<1xf32>
  } else {
    memref.store %one, %A[%c0] : memref<1xf32>
  } {else_branch = true}
  return
}
