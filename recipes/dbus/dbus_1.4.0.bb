include dbus.inc

BBCLASSEXTEND = "native"

SRC_URI = "http://dbus.freedesktop.org/releases/dbus/dbus-${PV}.tar.gz"
SRC_URI += "file://tmpdir.patch file://dbus-1.init"

