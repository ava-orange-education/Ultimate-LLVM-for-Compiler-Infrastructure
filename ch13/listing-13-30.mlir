// Listing 13-30. Two identical additions, before CSE
// Run: mlir-opt --verify-roundtrip listing-13-30.mlir

func.func @redundant_add() -> i32 {
  %c1 = arith.constant 1 : i32
  %a = arith.addi %c1, %c1 : i32
  %b = arith.addi %c1, %c1 : i32
  return %b : i32
}
