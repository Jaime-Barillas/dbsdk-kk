(ns copy-koka-libs
  (:require
    [babashka.fs :as fs]))

;; Capture path to script when Babashka loads the file.
(def ^:private self-path *file*)

(defn- make-copy-fn [src-prefix dst-prefix]
  (fn [tree]
    (fs/copy-tree
      (fs/path src-prefix tree)
      (fs/path dst-prefix tree)
      {:replace-existing true})))

(defn -main [& args]
  ;; Prep Work
  (let [proj-root (-> self-path fs/parent fs/parent)
        koka-kklib-path (fs/path proj-root "lib" "koka" "kklib")
        koka-lib-path (fs/path proj-root "lib" "koka" "lib")
        koka-mimalloc-path (fs/path koka-kklib-path "mimalloc")
        dbsdk-kk-kklib-path (fs/path proj-root "sys" "kklib")
        dbsdk-kk-lib-path (fs/path proj-root "sys" "lib")
        dbsdk-kk-mimalloc-path (fs/path dbsdk-kk-kklib-path "mimalloc")]
    (when-not (fs/exists? koka-kklib-path)
      (println "Could not find the Koka C runtime!")
      (System/exit 1))
    (when-not (fs/exists? koka-lib-path)
      (println "Could not find the Koka standard library!")
      (System/exit 1))
    (when-not (fs/exists? koka-mimalloc-path)
      (println "Could not find Koka's mimalloc library!")
      (System/exit 1))

    ;; Copy The Files
    (run!
      (make-copy-fn koka-kklib-path dbsdk-kk-kklib-path)
      ["include" "src"])
    (run!
      (make-copy-fn koka-lib-path dbsdk-kk-lib-path)
      ["std"])
    (run!
      (make-copy-fn koka-mimalloc-path dbsdk-kk-mimalloc-path)
      ["include" "src"])))
