// x86-pat-compound.td -- the complete file.
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . x86-pat-compound.td -o /dev/null

// Excerpt: a real pattern from llvm/lib/Target/X86/X86InstrCompiler.td. A shift
// left by one has no dedicated instruction here, so it is matched onto an add of
// the register with itself -- one DAG node rewritten as a different instruction.
def : Pat<(shl GR32:$src1, (i8 1)), (ADD32rr GR32:$src1, GR32:$src1)>;
