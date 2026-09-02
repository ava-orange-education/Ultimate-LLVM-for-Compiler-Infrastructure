// Listing 12-42. Excerpt from MyArchISelLowering.cpp; the ellipsis stands for the full parameter list
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-42.td -o /dev/null

include "MyArchInstrInfo.td"

def MUL16x16 : MyArchInst<0b100000, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
                          "mul16x16 $rd, $rs1, $rs2", []>;
