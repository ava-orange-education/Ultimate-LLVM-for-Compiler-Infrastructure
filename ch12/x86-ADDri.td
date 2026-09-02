// x86-ADDri.td -- the complete file.
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . x86-ADDri.td -o /dev/null

// Excerpt: a simplified rendering of x86's ADD32ri, from
// llvm/lib/Target/X86/X86InstrArithmetic.td. I<> is defined in
// X86InstrUtils.td; GR32 and i32imm come from elsewhere in the X86 target.
//
// MRM0r is the right format for the immediate form: the opcode extension 0
// lives in the ModR/M reg field, which is what "MRM0r" names. MRMSrcReg would
// say the reg field holds a second register operand, which this form has not.
def ADDri : I<0x81, MRM0r,
              (outs GR32:$dst),
              (ins GR32:$lhs, i32imm:$imm),
              "add{l}\t{$imm, $dst|$dst, $imm}",
              [(set GR32:$dst, (add GR32:$lhs, imm:$imm))]> {
  let Constraints = "$lhs = $dst";
}

// The chapter's selection pattern for the instruction above. It must follow the def:
// ADDri is defined here, not by the X86 target, so this pattern is an excerpt of this
// file rather than of X86InstrArithmetic.td.
def : Pat<(add GR32:$a, imm:$b), (ADDri GR32:$a, imm:$b)>;

// The same selection written without operand classes on the output. Listing 12-6
// prints this shorthand and listing 12-13 the fully-classed form; both are accepted
// by TableGen in X86 context, so both are reproduced here against the one ADDri.
def : Pat<(add i32:$a, imm:$b), (ADDri $a, $b)>;
