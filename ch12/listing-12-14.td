// Listing 12-14. A register class and its allocation order

def GR64 : RegisterClass<"X86", [i64], 64, (add RAX, RBX, RCX, RDX)>;
