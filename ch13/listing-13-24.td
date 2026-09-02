// Listing 13-24. The same ODS file, revisited when writing the dialect
// Run: mlir-tblgen --gen-op-defs -I $LLVM_DIR/include listing-13-24.td -o /dev/null

include "mlir/IR/OpBase.td"
// Pure lives with the side-effect interfaces, not in OpBase.td.
include "mlir/Interfaces/SideEffectInterfaces.td"

def MyDialect : Dialect {
  let name = "mydsl";
  let cppNamespace = "::mydsl";
}

// Every operation in the dialect derives from this.
class MyDialect_Op<string mnemonic, list<Trait> traits = []>
    : Op<MyDialect, mnemonic, traits>;

def MyMatmulOp : MyDialect_Op<"matmul", [Pure]> {
  let summary = "Matrix multiply on two tensors";

  let arguments = (ins AnyTensor:$lhs, AnyTensor:$rhs);
  let results   = (outs AnyTensor:$result);

  let assemblyFormat = "$lhs `,` $rhs attr-dict `:` type($lhs) `,` type($rhs) `->` type($result)";
}
