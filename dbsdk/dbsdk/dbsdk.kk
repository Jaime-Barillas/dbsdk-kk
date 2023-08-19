module dbsdk/dbsdk

// Import custom wasi implementation for a subset of functions. This stops
// emscripten from generating imports for a few key functions.
extern import
  c file "wasi.c"