; Listing 6-5. Naming array and pointer types

%arrayty = type [2 x [3 x [4 x i32]]]   ; 2x3x4 array of 32-bit integers

%aptr = type ptr                        ; a pointer; what it points at is the

%funptr = type ptr                      ; instruction's business, not the pointer's

%strty = { float, %funptr }  ; A structure, where the first element is a 
                                                      ; float and the second element is the %funptr 
                                                      ; pointer to function type defined previously
