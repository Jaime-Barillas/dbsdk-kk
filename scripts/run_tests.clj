(ns run-tests
  (:require
    [babashka.fs :as fs]
    [babashka.process :as proc]))

;; Capture path to script when Babashka loads the file.
(def ^:private self-path *file*)

(defn- get-os []
  (let [os (System/getProperty "os.name")]
    (cond
      (re-find #"Windows" os) "windows"
      (re-find #"Linux" os) "ubuntu")))

(defn run-test [path]
  (let [cli-path (-> self-path fs/parent fs/parent (fs/path "cli" "dbsdk-kk"))]
    (proc/shell {:dir path} (str cli-path))))

(defn -main [& args]
  (let [test-dir (-> self-path fs/parent fs/parent (fs/path "tests"))
        tests (if (empty? *command-line-args*)
                (fs/list-dir test-dir)
                *command-line-args*)]
    (run! run-test tests)))

