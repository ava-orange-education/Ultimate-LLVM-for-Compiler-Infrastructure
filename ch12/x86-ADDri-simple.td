// x86-ADDri-simple.td -- the complete file.
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . x86-ADDri-simple.td -o /dev/null

// Excerpt: a simplified rendering of x86's ADD32ri. It is not standalone --
// I<> is defined in llvm/lib/Target/X86/X86InstrUtils.td, and GR32, i32imm and
// the MRM* formats come from elsewhere in the X86 target, so this compiles only
// as part of llvm/lib/Target/X86/X86InstrArithmetic.td.
def ADDri : I<0x81, MRM0r,
              (outs GR32:$dst),
              (ins GR32:$src, i32imm:$imm),
              "add{l}\t{$imm, $dst|$dst, $imm}",
              [(set GR32:$dst, (add GR32:$src, imm:$imm))]> {
  // x86's ADD is two-address: the destination register is also the first
  // source. Without this constraint the definition describes a three-operand
  // add that the hardware does not have.
  let Constraints = "$src = $dst";
}
