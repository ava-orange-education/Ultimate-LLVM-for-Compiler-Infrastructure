include "llvm/Target/Target.td"

// Every register is 32 bits wide and carries its own encoding number.
class MyArchReg<bits<5> num, string n> : Register<n> {
  let Namespace = "MyArch";
  let HWEncoding{4-0} = num;
}

// Physical registers
def R0 : MyArchReg<0, "r0">, DwarfRegNum<[0]>;
def R1 : MyArchReg<1, "r1">, DwarfRegNum<[1]>;
def R2 : MyArchReg<2, "r2">, DwarfRegNum<[2]>;
def R3 : MyArchReg<3, "r3">, DwarfRegNum<[3]>;
def SP : MyArchReg<4, "sp">, DwarfRegNum<[4]>;

// The register class also fixes the allocation order. SP is defined here but
// reserved in MyArchRegisterInfo::getReservedRegs(), so it is never allocated.
def GPR : RegisterClass<"MyArch", [i32], 32, (add R0, R1, R2, R3, SP)>;
