// Listing 13-4. A dense tensor attribute
// Run: mlir-opt --verify-roundtrip listing-13-04.mlir

%0 = arith.constant dense<[[1, 2], [3, 4]]> : tensor<2x2xi32>
