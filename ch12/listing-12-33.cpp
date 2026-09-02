// Listing 12-33. Lowering formal arguments into registers

SDValue MyTargetLowering::LowerFormalArguments(...) {
  for (unsigned i = 0; i < Ins.size(); ++i) {
    if (i == 0)
      ArgLocs.push_back(R1);
    else if (i == 1)
      ArgLocs.push_back(R2);
  }
}
