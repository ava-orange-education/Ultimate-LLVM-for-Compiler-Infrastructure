// Listing 13-18. A loop that accumulates through iter_args
// Run: mlir-opt --verify-roundtrip listing-13-18.mlir

func.func @sum() -> i32 {
  // The loop bounds are index values; the accumulator is an i32.
  %lb = arith.constant 0 : index
  %ub = arith.constant 10 : index
  %step = arith.constant 1 : index
  %init = arith.constant 0 : i32

  %result = scf.for %i = %lb to %ub step %step iter_args(%sum = %init) -> (i32) {
    %i_i32 = arith.index_cast %i : index to i32
    %new = arith.addi %sum, %i_i32 : i32
    scf.yield %new : i32
  }
  return %result : i32
}
