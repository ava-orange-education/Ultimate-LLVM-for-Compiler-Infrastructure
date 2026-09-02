// Listing 13-1. The same arith.addi, in the core-dialects tour
// Run: mlir-opt --verify-roundtrip listing-13-01.mlir

func.func @add(%lhs: i32, %rhs: i32) -> i32 {
  %sum = arith.addi %lhs, %rhs : i32
  return %sum : i32
}
