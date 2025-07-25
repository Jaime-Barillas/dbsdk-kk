(ns setup-emscripten
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

;; The links are created by shelling out to mklink on Windows and ln on Linux.
(defn -main [& args]
  (let [version "4.0.11"
        os (get-os)
        proj-root (-> self-path fs/parent fs/parent)
        emsdk-dir (fs/path proj-root "tools" "emsdk")]

    (when-not os
      (println "Unsupported OS:" os)
      (System/exit 1))

    (println (str "Installing & activating emscripten v" version "..."))
    (proc/shell {:dir (str emsdk-dir)} "./emsdk" "install" version)
    (proc/shell {:dir (str emsdk-dir)} "./emsdk" "activate" version)))
