// Listing 12-38. Excerpt from MyArchISelLowering.cpp; the ellipsis stands for the full parameter list

MyTargetLowering::MyTargetLowering(const TargetMachine &TM,
                                   const TargetSubtargetInfo &STI)
    : TargetLowering(TM, STI) {
  setOperationAction(ISD::MUL,       MVT::i32, Custom);
  setOperationAction(ISD::SMUL_LOHI, MVT::i32, Expand);
  setOperationAction(ISD::UMUL_LOHI, MVT::i32, Expand);
  setOperationAction(ISD::MULHS,     MVT::i32, Expand);
  setOperationAction(ISD::MULHU,     MVT::i32, Expand);
}

SDValue MyTargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::MUL:
    return LowerMUL(Op, DAG);
  default:
    return SDValue();
  }
}
