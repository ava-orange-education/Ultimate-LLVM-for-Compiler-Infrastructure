// Listing 13-3. SSA values flowing from one operation to the next
// Run: mlir-opt --verify-roundtrip listing-13-03.mlir

%a = arith.constant 5 : i32
%b = arith.constant 3 : i32
%c = arith.addi %a, %b : i32
