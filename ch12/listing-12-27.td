// Listing 12-27. The same pattern, in the GlobalISel comparison

def : Pat<(add GR32:$lhs, imm:$rhs), (ADD32ri GR32:$lhs, imm:$rhs)>;
