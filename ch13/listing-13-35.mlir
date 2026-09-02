// Listing 13-35. An addition of zero, waiting to be folded
// Run: mlir-opt --verify-roundtrip listing-13-35.mlir

func.func @add_zero(%a: i32) -> i32 {
  // Adding a constant zero is what --canonicalize folds away: running
  //   mlir-opt --canonicalize
  // on this function leaves just `return %a`.
  %zero = arith.constant 0 : i32
  %sum = arith.addi %a, %zero : i32
  return %sum : i32
}
