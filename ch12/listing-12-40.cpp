// Listing 12-40. Excerpt from MyArchISelLowering.cpp; the ellipsis stands for the full parameter list

SDValue MyTargetLowering::LowerMUL(SDValue Op, SelectionDAG &DAG) const {
  SDLoc DL(Op);
  EVT VT = Op.getValueType();
  unsigned Bits = VT.getSizeInBits();
  unsigned Half = Bits / 2;
  SDValue LHS = Op.getOperand(0);
  SDValue RHS = Op.getOperand(1);

  // Fast path: both operands provably fit in the low half, so one 16x16 does it.
  APInt HiHalf = APInt::getHighBitsSet(Bits, Half);
  if (DAG.MaskedValueIsZero(LHS, HiHalf) && DAG.MaskedValueIsZero(RHS, HiHalf))
    return DAG.getNode(MyTargetISD::MUL16x16, DL, VT, LHS, RHS);

  SDValue Mask = DAG.getConstant(maskTrailingOnes<uint64_t>(Half), DL, VT);
  SDValue Shift = DAG.getShiftAmountConstant(Half, VT, DL);
  SDValue AL = DAG.getNode(ISD::AND, DL, VT, LHS, Mask);
  SDValue AH = DAG.getNode(ISD::SRL, DL, VT, LHS, Shift);
  SDValue BL = DAG.getNode(ISD::AND, DL, VT, RHS, Mask);
  SDValue BH = DAG.getNode(ISD::SRL, DL, VT, RHS, Shift);

  SDValue LoLo = DAG.getNode(MyTargetISD::MUL16x16, DL, VT, AL, BL);
  SDValue AlBh = DAG.getNode(MyTargetISD::MUL16x16, DL, VT, AL, BH);
  SDValue AhBl = DAG.getNode(MyTargetISD::MUL16x16, DL, VT, AH, BL);
  SDValue Mid = DAG.getNode(ISD::ADD, DL, VT, AlBh, AhBl);
  Mid = DAG.getNode(ISD::SHL, DL, VT, Mid, Shift);
  return DAG.getNode(ISD::ADD, DL, VT, LoLo, Mid);
}
