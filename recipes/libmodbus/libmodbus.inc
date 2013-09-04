DESCRIPTION = "A Modbus library for Linux, Mac OS X, FreeBSD, QNX and Win32"
HOMEPAGE = "http://www.libmodbus.org/"
LICENSE = "LGPL"

inherit autotools-autoreconf pkgconfig library

LIBMODBUS_TEST_APPS="\
    bandwidth-client bandwidth-server-many-up bandwidth-server-one \
    random-test-client random-test-server \
    unit-test-client unit-test-server \
    version"

do_install[postfuncs] += "do_install_modbus_tests"
do_install_modbus_tests () {
    mkdir -p ${D}${bindir}
    for testapp in ${LIBMODBUS_TEST_APPS}; do
        if [ ! -e ${S}/tests/.libs/$testapp ]; then
		mv ${S}/tests/$testapp ${S}/tests/.libs/
	fi
	install -m 0755 ${S}/tests/.libs/$testapp ${D}${bindir}
    done
}

PACKAGES =+ "${PN}-tests"
FILES_${PN}-tests = "${bindir}"
