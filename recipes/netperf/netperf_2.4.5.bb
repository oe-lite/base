require netperf.inc

PR_append = ".0"

SRC_URI_append += "file://config-site-multiple-files.patch;patch=1"

PARALLEL_MAKE = ""
