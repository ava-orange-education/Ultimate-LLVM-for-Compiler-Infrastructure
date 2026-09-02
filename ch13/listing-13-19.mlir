// Listing 13-19. Branching on a comparison
// Run: mlir-opt --verify-roundtrip listing-13-19.mlir

func.func @check(%x: i32) -> i32 {
  %c0 = arith.constant 0 : i32

  // The comparison predicate is a bare keyword, not a quoted string.
  %cond = arith.cmpi slt, %x, %c0 : i32

  %res = scf.if %cond -> (i32) {
    // arith.negf is floating-point only. Integer negation is 0 - x.
    %neg = arith.subi %c0, %x : i32
    scf.yield %neg : i32
  } else {
    scf.yield %x : i32
  }
  return %res : i32
}
