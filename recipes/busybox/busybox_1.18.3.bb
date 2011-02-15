require busybox.inc

SRC_URI_append += "file://udhcp-simple-script-route-del-dev-null.patch"
SRC_URI_append += "file://busybox-1.18.3-wget.patch"
