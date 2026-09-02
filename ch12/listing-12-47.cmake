# Listing 12-47. The CMake target that builds the backend

# CMake comments start with #, not //.
add_llvm_target(MyArchCodeGen
  MyArchAsmPrinter.cpp
  MyArchISelLowering.cpp
  MyArchInstrInfo.cpp
  MyArchRegisterInfo.cpp
  MyArchSubtarget.cpp
  MyArchTargetMachine.cpp
)
