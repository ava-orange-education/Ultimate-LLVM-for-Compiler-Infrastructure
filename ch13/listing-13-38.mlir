// Listing 13-38. Structured control flow, before lowering
// Run: mlir-opt --verify-roundtrip listing-13-38.mlir

// Structured control flow, before lowering. scf.if carries its two branches as
// regions; the next listing shows the same thing after conversion to cf, where
// the regions have become basic blocks and explicit branches.
func.func @structured(%cond: i1) {
  scf.if %cond {
    scf.yield
  } else {
    scf.yield
  }
  return
}
