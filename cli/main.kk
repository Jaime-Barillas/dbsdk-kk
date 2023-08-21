/*==============================================================================
 dbsdk-kk cli tool
 -------------------------------
 The dbsdk-kk cli provides a convenient way to compile Koka code for the
 DreamBox fantasy console.
 -------------------------------
 TODO:
 + Koka's std/os/process/run-system-read does not seem to report errors.
 =============================================================================*/
import std/os/dir     // ensure-dir
//import std/os/env     // get-args
import std/os/file    // read-text-file write-text-file
import std/os/path    // appdir cwd stemname (/)
import std/os/process // run-system-read

val koka-opts = "--cc=emcc --target=wasm32 --fstdalloc --heap=16MB --stack=4MB --optimize=2"
val koka-cclinkopts = "--cclinkopts=\"-g0 -sWASM=1 -sWASM_BIGINT -sNO_FILESYSTEM -sERROR_ON_UNDEFINED_SYMBOLS=0 -sEXPORTED_FUNCTIONS=[_main,_malloc,_free]\""

fun compile-koka()
  val app-dir = appdir()
  val current-dir = cwd()
  // Appending the name of the main file to `current-dir` causes Koka to
  // generate a C file with _the full path_ as its name. Don't prepend the
  // current dir for a much nicer name!
  val koka-cmd = join(["koka",
                       koka-opts,
                       koka-cclinkopts,
                       "--sharedir=" ++ (app-dir / "sys").string,
                       "--builddir=" ++ (current-dir / ".koka").string,
                       "--include=" ++ (app-dir / "dbsdk").string,
                       "--ccincdir=" ++ (app-dir / "dbsdk").string,
                       "--output=" ++ (current-dir / ".dbsdk-kk" / "main").string,
                       "main.kk"],
                      " ")
  println(koka-cmd)
  ensure-dir(current-dir / ".dbsdk-kk")
  // NOTE: The koka compiler always returns an exit code of 0 even when it
  // encounters errors which prevent compilation.
  koka-cmd.run-system-read()
          .untry()
          .println()

fun wasm2wat()
  val wasm2wat = appdir() / "tools" / "wabt" / "wasm2wat"
  val current-dir = cwd()
  val wasm2wat-cmd = join([wasm2wat.string,
                           "--output=" ++ (current-dir / ".dbsdk-kk" / "main.wat").string,
                           (current-dir / ".dbsdk-kk" / "main.wasm").string],
                          " ")
  println(wasm2wat-cmd)
  ensure-dir(current-dir / ".dbsdk-kk")
  wasm2wat-cmd.run-system-read()
              .untry()
              .println()

fun patch-wat-file()
  val current-dir = cwd()
  val main-wat-file = current-dir / ".dbsdk-kk" / "main.wat"
  val output-file = current-dir / ".dbsdk-kk" / "main-patched.wat"
  val wat-file = read-text-file(main-wat-file)
  println("Patching Wasm module...")
  val patched-wat = wat-file.replace-all("(export \"__main_argc_argv", "(export \"main")
  write-text-file(output-file, patched-wat, False)

fun wat2wasm()
  val wat2wasm = appdir() / "tools" / "wabt" / "wat2wasm"
  val current-dir = cwd()
  val wat2wasm-cmd = join([wat2wasm.string,
                           "--output=" ++ (current-dir / "iso" / "main.wasm").string,
                           (current-dir / ".dbsdk-kk" / "main-patched.wat").string],
                          " ")
  println(wat2wasm-cmd)
  ensure-dir(current-dir / "iso")
  wat2wasm-cmd.run-system-read()
              .untry()
              .println()

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
  makedisc-cmd.run-system-read()
              .untry()
              .println()

fun main()
  with ctl throw-exn(exn)
    println(exn.message)
    match exn.info
      ExnAssert -> println("  Assert Error!")
      ExnError -> println("  Error Error!")
      ExnInternal(name) -> println("  Internal Error: " ++ name)
      ExnPattern(loc, def) -> println("  Pattern Error - loc: " ++ loc ++ ", def: " ++ def)
      ExnRange -> println("  Range Error!")
      ExnSystem(no) -> println("  System Error: " ++ no.show)
      ExnTodo -> println("  Todo Error!")
      _ -> println("  Unknown Error!")
  compile-koka()
  wasm2wat()
  patch-wat-file()
  wat2wasm()
  compile-iso()