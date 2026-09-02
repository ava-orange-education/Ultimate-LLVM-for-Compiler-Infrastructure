// Listing 13-50. affine: a loop over a memref
// Run: mlir-opt --verify-roundtrip listing-13-50.mlir

func.func @scale(%A: memref<100xf32>) {
  affine.for %i = 0 to 100 step 1 {
    %val = affine.load %A[%i] : memref<100xf32>
    %two = arith.constant 2.0 : f32
    %scaled = arith.mulf %val, %two : f32
    affine.store %scaled, %A[%i] : memref<100xf32>
  }
  return
}
