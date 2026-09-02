// Listing 9-34. a + b computed on one path only

if (cond) {
    t = a + b;
    ... use t ...
} else {
    ... // no computation of a+b here
}
// Later in code, a+b is needed on both paths.
