// Listing 13-2. A region nesting a loop body inside an operation
// Run: mlir-opt --verify-roundtrip listing-13-02.mlir

func.func private @print_i32(i32)

func.func @loop() {
  // scf.for bounds are index, not i32 -- that is what the induction variable is.
  %lb = arith.constant 0 : index
  %ub = arith.constant 10 : index
  %step = arith.constant 1 : index
  %c5 = arith.constant 5 : i32

  scf.for %i = %lb to %ub step %step {
    // %i is an index, so it must be cast before it can be added to an i32.
    %i_i32 = arith.index_cast %i : index to i32
    %val = arith.addi %i_i32, %c5 : i32
    func.call @print_i32(%val) : (i32) -> ()
  }
  return
}
