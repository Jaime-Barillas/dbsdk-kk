(ns download-xorriso
  (:require
    [babashka.fs :as fs]
    [babashka.http-client :as http]
    [babashka.process :as proc]))

;; Capture path to script when Babashka loads the file.
(def ^:private self-path *file*)

(defn- get-os []
  (let [os (System/getProperty "os.name")]
    (cond
      (re-find #"Linux" os) "ubuntu")))

(defn -main [& args]
  ;; Prep Work
  (let [version "1.5.6.pl02"
        os (get-os)
        download-url (str "https://www.gnu.org/software/xorriso/xorriso-" version ".tar.gz")
        download-dir (-> self-path fs/parent fs/parent (fs/path "tools" "xorriso"))
        archive (fs/path download-dir "xorriso.tar.gz")
        extracted-dir (fs/path download-dir (str "xorriso-1.5.6"))]

    (when-not os
      (println "Unsupported OS:" os)
      (System/exit 1))

    ;; Download and Extract
    (fs/create-dirs download-dir)
    (when (or (not (fs/exists? archive)) (some #{"-f" "--force"} args))
      (println "Downloading GNU xorriso...")
      (->> (http/get download-url {:as :bytes})
        :body
        (fs/write-bytes archive)))

    (println "Extracting GNU xorriso...")
    (proc/shell {:dir (str download-dir)} "tar" "-xf" (str archive))

    (println "Building GNU xorriso...")
    (proc/shell {:dir extracted-dir}
      "./configure"
      "--disable-shared"
      "--disable-readline"
      "--disable-libacl"
      "--disable-xattr"
      "--disable-zlib"
      "--disable-external-filters"
      "--disable-launch-frontend")
    (proc/shell {:dir extracted-dir} "make")))

