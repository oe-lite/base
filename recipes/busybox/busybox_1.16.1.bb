require busybox.inc

INC_PR = ".1"

SRC_URI_append += "file://udhcp-simple-script-route-del-dev-null.patch;patch=1"
