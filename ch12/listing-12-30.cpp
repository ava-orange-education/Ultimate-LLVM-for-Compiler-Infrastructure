// Listing 12-30. Emitting instruction bytes with MCCodeEmitter
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-12-30.cpp

#include "llvm/ADT/SmallVector.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSubtargetInfo.h"

using namespace llvm;

// Emit a conditional branch to `Target`. `Opcode` is X86::JCC_1 when called
// from inside the X86 backend.
void emitConditionalJump(const MCCodeEmitter &Emitter, unsigned Opcode,
                         const MCExpr *Target, const MCSubtargetInfo &STI,
                         SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups) {
  MCInst JCC;
  JCC.setOpcode(Opcode);
  JCC.addOperand(MCOperand::createExpr(Target));

  // The displacement is not known yet: the target label may not have been laid
  // out. encodeInstruction writes the opcode bytes and appends an MCFixup
  // describing the hole, which the assembler backend resolves once addresses
  // are final -- or hands to the linker as a relocation if it cannot.
  Emitter.encodeInstruction(JCC, CB, Fixups, STI);
}
