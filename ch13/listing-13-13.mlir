// Listing 13-13. scf.if yielding a value from both regions
// Run: mlir-opt --verify-roundtrip listing-13-13.mlir

func.func @select(%cond: i1, %a: i32, %b: i32) -> i32 {
  // scf.if yields a value only when a result type is declared; both regions must
  // then yield one. The region terminator is scf.yield.
  %res = scf.if %cond -> (i32) {
    scf.yield %a : i32
  } else {
    scf.yield %b : i32
  }
  return %res : i32
}

func.func @side_effect_only(%cond: i1, %A: memref<1xf32>) {
  %c0 = arith.constant 0 : index
  %one = arith.constant 1.0 : f32

  // With no result type, scf.yield takes no operands and may be omitted.
  scf.if %cond {
    memref.store %one, %A[%c0] : memref<1xf32>
  }
  return
}
