#!/usr/bin/env nu

def main [--force (-f): bool] {
  # Prep Work
  let version = '1.0.33'
  # TODO: Test on Ubuntu OS
  let os = ($nu.os-info | get name | str downcase)
  let download_url = $'https://github.com/WebAssembly/wabt/releases/download/($version)/wabt-($version)-($os).tar.gz'
  let download_dir = ($env.FILE_PWD | path join .. lib wabt)
  let archive = ($download_dir | path join wabt.tar.gz)
  let extracted_dir = ($download_dir | path join $'wabt-($version)')

  # Download and Extract
  mkdir $download_dir

  if (not ($archive | path exists)) or ($force == true) {
    print 'Downloading WABT...'
    curl -sSLo $archive $download_url
  }
  
  print "Extracting WABT..."
  tar -xf $archive -C $download_dir
  if ($download_dir | path join bin | path exists) {
    rm -rf ($download_dir | path join bin)
  }
  mv ($extracted_dir | path join bin) $download_dir
  rm -rf $extracted_dir
}