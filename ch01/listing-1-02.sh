# Listing 1-2. The array-bounds warning Clang reports for it
# Run: bash listing-1-02.sh

clang -fsyntax-only example.c

# example.c:5:43: warning: array index 10 is past the end of the array (that has type 'int[5]') [-Warray-bounds]



#     5 |     printf("Element at index 10 is %d\n", arr[10]); // Out-of-bounds access



#       |                                           ^   ~~


# example.c:4:5: note: array 'arr' declared here



#     4 |     int arr[5] = {1, 2, 3, 4, 5};



#       |     ^


# 1 warning generated.
