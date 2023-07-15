# `--fstdalloc` And a Modified Standard Library

**Context** - Compiling Koka code to Wasm with emscripten and a `--heap` of
16MiB results in a Wasm module that crashes when run with wasmer. Lowering the
`--stack` to 4MiB results in a Wasm module that runs with wasmer (with
warnings,) but crashes with DreamBox. The crash occurs within mimalloc.

**Solution** - Compile Koka without mimalloc using the (hidden, no longer
supported?) `--fstdalloc` option. Doing so causes emscripten to error within
the generated C code about usage of an undeclared function from kklib. The
simplest fix is to modify the standard library and tell the Koka compiler to
use our modified version. Note that the generated C code does #include the
kklib header, which means it should have access to the missing function
declaration even though the compiler says it doesn't. The problematic function
is: `kk_cctx_copy_apply` used by `kk_cctx_apply_nonlinear` in the
`sys/lib/std/core/types-cctx-inline.h` file. See the `FIXME:` note in that file.
