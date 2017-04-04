SUMMARY = "Real-Time preemption testcases"
HOMEPAGE = "https://rt.wiki.kernel.org/index.php/Cyclictest"
LICENSE = "GPL-2.0"

SRC_URI = "git://git.kernel.org/pub/scm/utils/rt-tests/rt-tests.git;${SRC_REV}"
SRC_REV ?= "tag=v${PV}"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit make c

S = "${SRCDIR}/${PN}"

# Calling 'uname -m' is broken on crossbuilds. NUMA is (still)
# irrelevant to most embedded systems, so for now just unconditionally
# disable it.
EXTRA_OEMAKE += "NUMA=0"

# Explicitly give these to make
EXTRA_OEMAKE += "prefix=${prefix}"
EXTRA_OEMAKE += "bindir=${bindir}"
EXTRA_OEMAKE += "mandir=${mandir}"

DEPENDS += "librt libpthread libdl"

inherit auto-package-utils

AUTO_PACKAGE_UTILS = "\
    cyclictest \
    hackbench \
    pip_stress \
    pi_stress \
    pmqtest \
    ptsematest \
    rt-migrate-test \
    sendme \
    signaltest \
    sigwaittest \
    svsematest \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc libpthread libdl librt"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libpthread libdl librt"

# hwlatdetect is a python script. It is installed unless one passes
# PYLIB=''. The default value of PYLIB is autodetected in the Makefile
# by
#
# PYLIB  ?= $(shell python -c 'import distutils.sysconfig;  print distutils.sysconfig.get_python_lib()')
#
# which is obviously broken for cross-builds, as well as broken if
# python happens to mean python3.
#
# Let the user define the proper value of PYLIB if he wants it (it's
# something like /usr/lib/python2.7/dist-packages) via a USE flag.

RECIPE_FLAGS += "rt_tests_pylib"
AUTO_PACKAGE_UTILS:>USE_rt_tests_pylib = " hwlatdetect"
FILES_${PN}-hwlatdetect += "${PYLIB}/hwlatdetect.py"
RDEPENDS_${PN}-hwlatdetct += "python"

PYLIB = ""
PYLIB:USE_rt_tests_pylib = "${USE_rt_tests_pylib}"
EXTRA_OEMAKE += "PYLIB='${PYLIB}'"

PACKAGES += "${PN}-backfire-src"
FILES_${PN}-backfire-src = "${prefix}/src/backfire"

RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"
