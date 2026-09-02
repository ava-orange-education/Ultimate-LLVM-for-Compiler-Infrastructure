// Listing 11-26. Reusing a compiled object instead of recompiling

if (cache.contains(fingerprint))
    JIT->addObjectFile(cache.get(fingerprint));
else {
    JIT->addIRModule(...);
    cache.save(fingerprint, generatedObject);
}
