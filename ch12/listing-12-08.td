// Listing 12-8. What a Register record holds
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-08.td -o /dev/null

class Register<string n> {
  string Name = n;
}
def RAX : Register<"RAX">;
def RBX : Register<"RBX">;
