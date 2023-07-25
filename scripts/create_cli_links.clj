(ns create-cli-links
  (:require
    [babashka.fs :as fs]
    [babashka.process :as proc]))

;; Capture path to script when Babashka loads the file.
(def ^:private self-path *file*)

(defn- get-os []
  (let [os (System/getProperty "os.name")]
    (cond
      (re-find #"Windows" os) "windows"
      (re-find #"Linux" os) "ubuntu"))) ; Just assume Ubuntu.

(defn- create-sym-link [target name]
  (try
    (case (get-os)
      "windows"
      (proc/shell (format "cmd /c \"mklink /j %s %s\"" name target))

      "ubuntu"
      (proc/shell (format "ln -s %s %s" target name)))
    (catch Exception ex
      (println "Error creating symlink " name "->" target "\n"))))

;; The links are created by shelling out to mklink on Windows and ln on Linux.
(defn -main [& args]
  (let [proj-root (-> self-path fs/parent fs/parent)
        cli-dir (fs/path proj-root "cli")]
    (create-sym-link (str (fs/path proj-root "dbsdk")) (str (fs/path cli-dir "dbsdk")))
    (create-sym-link (str (fs/path proj-root "sys")) (str (fs/path cli-dir "sys")))
    (create-sym-link (str (fs/path proj-root "tools")) (str (fs/path cli-dir "tools")))
    (create-sym-link (str (fs/path proj-root "wasi")) (str (fs/path cli-dir "wasi")))))
