### Prep Work

let koka_stdlib_path = ($env.FILE_PWD | path join .. lib/koka/lib | path expand)
let koka_kklib_path = ($env.FILE_PWD | path join .. lib/koka/kklib | path expand)
let dbsdk_kk_sys_dir = ($env.FILE_PWD | path join .. sys | path expand)
let dbsdk_kk_stdlib_path = ($dbsdk_kk_sys_dir | path join lib | path expand)
let dbsdk_kk_kklib_path = ($dbsdk_kk_sys_dir | path join kklib | path expand)

if not ($koka_stdlib_path | path exists) {
  print 'Could not find Koka standard library!'
  return 1
}

if not ($koka_kklib_path | path exists) {
  print 'Could not find Koka C runtime library!'
  return 1
}

# Ensure directories for Koka's stdlib and C runtime library exist.
mkdir -v ($dbsdk_kk_stdlib_path | path join std)
mkdir -v $dbsdk_kk_kklib_path
mkdir -v ($dbsdk_kk_kklib_path | path join mimalloc)

### Copy The Files

def make_file_copy [src_prefix: string, dst_prefix: string] {
  {|x, acc|
    cp -r ($src_prefix | path join $x.src) ($dst_prefix | path join $x.dst)
    null
  }
}

# TODO: Copy only what's needed?
let koka_stdlib_files = [['src'               , 'dst'];
                         ['std/core.kk'       , 'std/']
                         ['std/core/'    , 'std/core']]
let koka_kklib_files  = [['src'               , 'dst'];
                         ['include/'          , 'include']
                         ['src/'              , 'src']
                         ['mimalloc/include/' , 'mimalloc/include']
                         ['mimalloc/src/'     , 'mimalloc/src']]

$koka_stdlib_files | reduce -f null (make_file_copy $koka_stdlib_path $dbsdk_kk_stdlib_path)
$koka_kklib_files | reduce -f null (make_file_copy $koka_kklib_path $dbsdk_kk_kklib_path)
