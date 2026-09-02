// Listing 13-12. The shape of a .mlir file
// Run: mlir-opt --verify-roundtrip listing-13-12.mlir

module {
  func.func @add(%a: i32, %b: i32) -> i32 {   // Function named 'add' with 2 args
    %sum = arith.addi %a, %b : i32		// Arithmetic add operation
    return %sum : i32				// Return result
  }
}
