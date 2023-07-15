//import std/os/env     // get-args
import std/os/path    // appdir cwd stemname (/)
import std/os/process // run-system-read

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
                       "--output=" ++ (current-dir / "iso" / "main").string,
                       (current-dir / "main.kk").string],
                      " ")
  println(koka-cmd)
  match run-system-read(koka-cmd)
    Ok(result) -> println(result)
    Error -> ()

fun main()
  with ctl throw-exn(exn)
    println(exn.message)
  compile-koka()