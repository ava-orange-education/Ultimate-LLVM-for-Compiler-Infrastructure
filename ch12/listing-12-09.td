// Listing 12-9. Fields of an instruction record
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-09.td -o /dev/null

class ExampleRecord {
string Name = "RAX";
bits<3> Opcode = 0b101;

}
