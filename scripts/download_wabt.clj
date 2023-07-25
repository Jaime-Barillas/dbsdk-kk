(ns download-wabt
  (:require
    [babashka.fs :as fs]
    [babashka.http-client :as http]
    [babashka.process :as proc]))

;; Capture path to script when Babashka loads the file.
(def ^:private self-path *file*)

(defn- get-os []
  (let [os (System/getProperty "os.name")]
    (cond
      (re-find #"Windows" os) "windows"
      (re-find #"Linux" os) "ubuntu")))

(defn -main [& args]
  ;; Prep Work
  (let [version "1.0.33"
        os (get-os)
        download-url (str "https://github.com/WebAssembly/wabt/releases/download/" version "/wabt-" version "-" os ".tar.gz")
        download-dir (-> self-path fs/parent fs/parent (fs/path "tools" "wabt"))
        archive (fs/path download-dir "wabt.tar.gz")
        extracted-dir (fs/path download-dir (str "wabt-" version))]

    (when-not os
      (println "Unsupported OS:" os)
      (System/exit 1))

    ;; Download and Extract
    (fs/create-dirs download-dir)
    (when (or (not (fs/exists? archive)) (some #{"-f" "--force"} args))
      (println "Downloading WABT...")
      (->> (http/get download-url {:as :bytes})
        :body
        (fs/write-bytes archive)))

    (println "Extracting WABT...")
    (proc/shell {:dir (str download-dir)} "tar" "-xf" (str archive))
    (fs/copy-tree (fs/path extracted-dir "bin") download-dir {:replace-existing true})
    (fs/delete-tree extracted-dir)))
