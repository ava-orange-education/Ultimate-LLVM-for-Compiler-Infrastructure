// Listing 10-51. Mixing types from two different contexts

Module *M1 = new Module(..., Context1);
Type *T = Type::getInt32Ty(Context2); // from another context
