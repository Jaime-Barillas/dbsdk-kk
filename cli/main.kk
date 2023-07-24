import std/os/dir     // ensure-dir
//import std/os/env     // get-args
import std/os/file    // read-text-file write-text-file
import std/os/path    // appdir cwd stemname (/)
import std/os/process // run-system-read
import wat/parser
import wat/patcher

val koka-opts = "--cc=emcc --target=wasm32 --fstdalloc --heap=16MB --stack=4MB --optimize=2"
val koka-cclinkopts = "--cclinkopts=\"-g0 -sWASM=1 -sWASM_BIGINT -sNO_FILESYSTEM -sERROR_ON_UNDEFINED_SYMBOLS=0 -sEXPORTED_FUNCTIONS=[_main,_malloc,_free]\""

fun compile-koka()
  val app-dir = appdir()
  val current-dir = cwd()
  val koka-cmd = join(["koka",
                       koka-opts,
                       koka-cclinkopts,
                       "--sharedir=" ++ (app-dir / "sys").string,
                       "--builddir=" ++ (current-dir / ".koka").string,
                       "--include=" ++ (app-dir / "dbsdk").string,
                       "--output=" ++ (current-dir / ".dbsdk-kk" / "main").string,
                       (current-dir / "main.kk").string],
                      " ")
  println(koka-cmd)
  ensure-dir(current-dir / ".dbsdk-kk")
  match run-system-read(koka-cmd)
    Ok(result) -> println(result)
    Error -> ()

fun wasm2wat()
  val wasm2wat = appdir() / "tools" / "wabt" / "wasm2wat"
  val current-dir = cwd()
  val wasm2wat-cmd = join([wasm2wat.string,
                           "--output=" ++ (current-dir / ".dbsdk-kk" / "main.wat").string,
                           (current-dir / ".dbsdk-kk" / "main.wasm").string],
                          " ")
  println(wasm2wat-cmd)
  ensure-dir(current-dir / ".dbsdk-kk")
  match run-system-read(wasm2wat-cmd)
    Ok(result) -> println(result)
    Error -> ()

// FIXME: This should be in the wat/patcher.kk file.
fun rename-main-export(field: module-field): _ module-field
  match field
    Export(src, name, func-idx) ->
      if name == "__main_argc_argv" then
        // At this point, the `name` used by the Export type doesn't matter.
        // We only need to update the actual source text.
        val new-src = src.replace-all("__main_argc_argv", "main")
        Export(new-src, name, func-idx)
      else
        Export(src, name, func-idx)
    _ -> field

fun patch-wat-file()
  val current-dir = cwd()
  val main-wat-file = current-dir / ".dbsdk-kk" / "main.wat"
  val output-file = current-dir / ".dbsdk-kk" / "main-patched.wat"
  val wat-file = read-text-file(main-wat-file)
  val wasi-file = read-text-file(appdir() / "wasi" / "wasi.wat")
  val main-wat-module = match parse-wat(wat-file)
    ParseError -> []
    ParseOk(res, _) -> res
  val first-field = main-wat-module.head(Other("")) // Starting "(module".
  val module-tail = main-wat-module.tail // Grab everything patch() won't touch.
                                   .drop-while(fn (x) !(x.is-other))
                                   .map(rename-main-export) // FIXME: Move to wat/patcher.kk file.
  val wasi-module = match parse-wat(wasi-file)
    ParseError -> []
    ParseOk(res, _) -> res
  println("Patching Wasm module...")
  val patched-wat-module = patch(main-wat-module, wasi-module)
  val final-module = Cons(first-field, patched-wat-module ++ module-tail)
  write-text-file(output-file, final-module.map(src).join, False)

fun wat2wasm()
  val wat2wasm = appdir() / "tools" / "wabt" / "wat2wasm"
  val current-dir = cwd()
  val wat2wasm-cmd = join([wat2wasm.string,
                           "--output=" ++ (current-dir / "iso" / "main.wasm").string,
                           (current-dir / ".dbsdk-kk" / "main-patched.wat").string],
                          " ")
  println(wat2wasm-cmd)
  ensure-dir(current-dir / "iso")
  match run-system-read(wat2wasm-cmd)
    Ok(result) -> println(result)
    Error -> ()

fun compile-iso()
  val makedisc = appdir() / "tools" / "makedisc"
  val current-dir = cwd()
  val proj-name = current-dir.stemname
  val makedisc-cmd = join([makedisc.string,
                           "--label",
                           proj-name,
                           "--output",
                           (current-dir / (proj-name ++ ".iso")).string,
                           (current-dir / "iso").string],
                          " ")
  println(makedisc-cmd)
  match run-system-read(makedisc-cmd)
    Ok(result) -> println(result)
    Error -> ()

fun main()
  with ctl throw-exn(exn)
    println(exn.message)
  compile-koka()
  wasm2wat()
  patch-wat-file()
  wat2wasm()
  compile-iso()