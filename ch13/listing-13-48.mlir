// Listing 13-48. scf: a counted loop
// Run: mlir-opt --verify-roundtrip listing-13-48.mlir

func.func @loop() {
  // scf.for bounds are index values, and so is the induction variable.
  %lb = arith.constant 0 : index
  %ub = arith.constant 10 : index
  %step = arith.constant 1 : index
  %c1 = arith.constant 1 : i32

  scf.for %i = %lb to %ub step %step {
    %i_i32 = arith.index_cast %i : index to i32
    %res = arith.addi %i_i32, %c1 : i32
  }
  return
}
