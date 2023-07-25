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
        koka-stdlib-path (fs/path proj-root "lib" "koka" "lib")
        koka-kklib-path (fs/path proj-root "lib" "koka" "kklib")
        dbsdk-kk-sys-path (fs/path proj-root "sys")
        dbsdk-kk-stdlib-path (fs/path dbsdk-kk-sys-path "lib")
        dbsdk-kk-kklib-path (fs/path dbsdk-kk-sys-path "kklib")]
    (when-not (fs/exists? koka-stdlib-path)
      (println "Could not find Koka standard library!")
      (System/exit 1))
    (when-not (fs/exists? koka-kklib-path)
      (println "Could not find Koka C runtime library!")
      (System/exit 1))

    ;; Copy The Files
    ;; TODO: Copy only what's needed?
    (fs/create-dirs (fs/path dbsdk-kk-stdlib-path "std")) ; Needed for std/core.kk
    (fs/create-dirs (fs/path dbsdk-kk-stdlib-path "std" "num")) ; For int32/int64/float64 files
    (doseq [f [(fs/path "std" "core.kk")
               (fs/path "std" "num" "int32.kk")
               (fs/path "std" "num" "int64.kk")
               (fs/path "std" "num" "float64-inline.c")
               (fs/path "std" "num" "float64.kk")]]
      (fs/copy
        (fs/path koka-stdlib-path f)
        (fs/path dbsdk-kk-stdlib-path f)
        {:replace-existing true}))
    (run!
      (make-copy-fn koka-stdlib-path dbsdk-kk-stdlib-path)
      ["std/core"])
    (run!
      (make-copy-fn koka-kklib-path dbsdk-kk-kklib-path)
      ["include" "src"])))
