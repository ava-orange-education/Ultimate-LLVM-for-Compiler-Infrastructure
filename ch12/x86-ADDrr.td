// x86-ADDrr.td -- the complete file.
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . x86-ADDrr.td -o /dev/null

// Excerpt: a simplified rendering of x86's ADD32rr, from
// llvm/lib/Target/X86/X86InstrArithmetic.td. I<> is defined in
// X86InstrUtils.td; GR32 and the MRM* formats come from elsewhere in the X86
// target, so this is not standalone.
def ADDrr : I<0x01, MRMDestReg,
              (outs GR32:$dst),
              (ins GR32:$lhs, GR32:$rhs),
              "add{l}\t{$rhs, $dst|$dst, $rhs}",
              [(set GR32:$dst, (add GR32:$lhs, GR32:$rhs))]> {
  // Two-address: $lhs and $dst are the same register.
  let Constraints = "$lhs = $dst";
}
