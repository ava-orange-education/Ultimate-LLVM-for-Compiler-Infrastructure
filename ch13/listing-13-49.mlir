// Listing 13-49. func: a function and its return
// Run: mlir-opt --verify-roundtrip listing-13-49.mlir

func.func @main(%arg0: i32) -> i32 {
  return %arg0 : i32
}
