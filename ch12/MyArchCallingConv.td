include "MyArchInstrInfo.td"

// Arguments: promote anything narrower than 32 bits, then pass in R0-R3, and
// spill to the stack once those run out. CCAssignToReg is positional already --
// it hands out the listed registers in order and falls through to the next rule
// when the list is exhausted.
def CC_MyArch : CallingConv<[
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,
  CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

// Return values: a single i32 comes back in R0.
def RetCC_MyArch : CallingConv<[
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,
  CCIfType<[i32], CCAssignToReg<[R0]>>
]>;

// Callee-saved registers, read by MyArchRegisterInfo::getCalleeSavedRegs().
def CSR_MyArch : CalleeSavedRegs<(add R2, R3)>;
