# Setup, Scripts, & Compilation

It is expected that you have tar, curl, and [babashka](https://babashka.org).
Babashka is used to execute the Clojure scripts in a crossplatform manner.

# `--fstdalloc` And a Modified kklib

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

# Custom WASI Implementation

Koka expects a WASI environment for its Wasm output. DreamBox does not provide
any WASI implementation. In order to get Koka code to run, the subset of WASI
functions that Koka requires are stubbed out with minimal implementations. For
most of the functions these implementations either do nothing and report
success/failure or trap execution. A proper working implementation isn't
needed to run the Koka code successfully in DreamBox. The file containing the
custom implementation, wasi.c, is part of the DBSDK Koka wrapper so that it is
included in compilation and available for linking when building a game.

# dbsdk-kk

The goal of dbsdk-kk is to provide a Koka wrapper around the DreamBox SDK for
C/C++. The wrapper is intended to closely mirror the C/C++ code wherever
possible. It also provides a cli tool that works similarly to DreamBox's
official Rust CLI.

## Compiling Koka for DreamBox

Compiling Koka for DreamBox (via the cli) goes through a 5-step process:
1. **Compile the Koka to Wasm** - Koka is compiled to the `wasm32` target.
   The path to the DBSDK wrapper and the custom WASI functions are provided to
   the compiler.
2. **Convert the Wasm output to Wat format** - This is done via the `wasm2wat`
   tool from the WABT.
3. **Patch the Wat file** - The only thing that needs to be done here is to
   change the name of the main function export. It is generated as
   `__main_argc_argv` yet DreamBox wants it to be `main`. Note that it is
   _not_ the `_start` function which is renamed to `main`, I believe this is
   how it works with the Rust DBSDK (though perhaps double check.)
4. **Convert the patched Wat file back to Wasm** - This is done via the
   `wat2wasm` tool from the WABT.
5. **Compile the ISO** - We use the makedisc tool from the DreamBox SDK.

## The SDK

The DBSDK Koka wrapper tries to expose the C/C++ functions with as thin a layer
as is reasonable. Due to the differences between Koka and C/C++, the DBSDK
cannot be used directly (for the most part.) In these cases a wrapping C
function is created and called instead. Koka versions of the structs declared
by the DBSDK are provided as well so the end-user doesn't have to muck about
with wrapping the structs his/herself.