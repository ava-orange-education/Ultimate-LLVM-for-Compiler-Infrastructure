// Listing 12-32. One instruction written out without the format class
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-32.td -o /dev/null

include "MyArchInstrInfo.td"

// Spelling one instruction out in full, rather than through the ALUrr helper,
// shows what the format class actually sets. Instruction has no Parser field --
// the assembly syntax lives in AsmString and the selection pattern in Pattern.
def ADDrr_explicit : MyArchInst<0b000001,
                                (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
                                "add $rd, $rs1, $rs2",
                                [(set i32:$rd, (add i32:$rs1, i32:$rs2))]>;
