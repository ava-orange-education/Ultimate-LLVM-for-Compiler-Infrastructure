// Listing 13-9. A loop, a function and a return in one module
// Run: mlir-opt --verify-roundtrip listing-13-09.mlir

func.func @compute() -> i32 {
  // The loop bounds are index values; the accumulator carried by iter_args is an i32.
  %lb = arith.constant 0 : index
  %ub = arith.constant 10 : index
  %step = arith.constant 1 : index
  %init = arith.constant 0 : i32

  %result = scf.for %i = %lb to %ub step %step iter_args(%acc = %init) -> (i32) {
    %i_i32 = arith.index_cast %i : index to i32
    %next = arith.addi %acc, %i_i32 : i32
    scf.yield %next : i32
  }
  return %result : i32
}
