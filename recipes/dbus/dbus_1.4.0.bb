include dbus.inc

BBCLASSEXTEND = "native"

SRC_URI = "\
  http://dbus.freedesktop.org/releases/dbus/dbus-${PV}.tar.gz \
  \
  file://tmpdir.patch;patch=1 \
#  file://add-configurable-reply-timeouts.patch;patch=1 \
  file://dbus-1.init \
"            

