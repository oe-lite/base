include tslib.inc

SRC_URI += "file://fix_version.patch"
SRC_URI += "file://newer-libtool-fix.patch"
SRC_URI += "file://tslib-nopressure.patch"
SRC_URI += "file://tslib-pluginsld.patch"

do_configure_prepend () {
        ./autogen.sh
}
