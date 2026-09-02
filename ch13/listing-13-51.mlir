// Listing 13-51. The same linalg.matmul, in the dialect tour
// Run: mlir-opt --verify-roundtrip listing-13-51.mlir

func.func @matmul(%A: tensor<4x4xf32>, %B: tensor<4x4xf32>,
                  %C: tensor<4x4xf32>) -> tensor<4x4xf32> {
  // On tensors linalg.matmul produces a value, so the result type is part of the
  // operation and the result can be named. The memref form writes into outs
  // instead and yields nothing -- naming that one is what the parser rejects.
  %res = linalg.matmul ins(%A, %B : tensor<4x4xf32>, tensor<4x4xf32>)
                       outs(%C : tensor<4x4xf32>) -> tensor<4x4xf32>
  return %res : tensor<4x4xf32>
}
