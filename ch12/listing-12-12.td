// Listing 12-12. A TableGen pattern that selects ADDri

def : Pat<(add GR32:$a, imm:$b), (ADDri GR32:$a, imm:$b)>;
