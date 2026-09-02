// Listing 13-41. The same llvm-dialect module, in the dialect tour
// Run: mlir-opt --verify-roundtrip listing-13-41.mlir

llvm.func @add(%a: i32, %b: i32) -> i32 {
  %sum = llvm.add %a, %b : i32
  llvm.return %sum : i32
}
