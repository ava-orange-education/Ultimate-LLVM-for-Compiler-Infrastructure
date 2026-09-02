// Listing 13-34. The pattern that performs the lowering

struct LowerMatmulPattern : public OpRewritePattern<mydsl::MatmulOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(mydsl::MatmulOp op,
                                PatternRewriter &rewriter) const override {
    auto loc = op.getLoc();
    Value lhs = op.getLhs();
    Value rhs = op.getRhs();

    // Type::cast<T>() was removed in LLVM 21; use the free function mlir::cast<T>.
    auto resultType = mlir::cast<ShapedType>(op.getResult().getType());

    // linalg::InitTensorOp no longer exists -- it became tensor::EmptyOp, which
    // takes the shape and the element type.
    Value out = tensor::EmptyOp::create(rewriter, loc, resultType.getShape(),
                                        resultType.getElementType());

    auto matmul = linalg::MatmulOp::create(rewriter, loc,
                                           TypeRange{resultType},
                                           ValueRange{lhs, rhs},
                                           ValueRange{out});

    rewriter.replaceOp(op, matmul.getResult(0));
    return success();
  }
};
