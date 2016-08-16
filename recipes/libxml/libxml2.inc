DESCRIPTION = "GNOME XML Parser library"

RECIPE_TYPES = "machine native sdk"

inherit autotools make-vpath pkgconfig library binconfig

SRC_URI = "ftp://xmlsoft.org/${PN}/${PN}-${PV}.tar.gz"

DEPENDS = "libc libm ${DEPENDS_HOST_OS} ${DEPENDS_PYTHON}"
DEPENDS_PYTHON = ""
DEPENDS_PYTHON:native = "python2 python2-distutils python2-dev"
DEPENDS_HOST_OS = "libdl"
DEPENDS_HOST_OS:HOST_LIBC_mingw = ""
DEPENDS_${PN} += "libc libm ${DEPENDS_HOST_OS}"

EXTRA_OECONF_PYTHON += "--with-python-install-dir=${PYDIR}/site-packages"
EXTRA_OECONF_PYTHON:machine = "--without-python"
EXTRA_OECONF_PYTHON:sdk = "--without-python"

EXTRA_OECONF = "\
 --without-legacy \
 --with-c14n \
 ${EXTRA_OECONF_PYTHON}"

LDFLAGS_LDL = "-ldl"
LDFLAGS_LDL:TARGET_OS_mingw32 = ""
export LDFLAGS += "${LDFLAGS_LDL}"

PACKAGES += "${PN}-utils ${PN}-python ${PN}-python-dev ${PN}-python-dbg"
FILES_${PN} = "${libexecdir}/* ${sharedlibdir}/lib*${SOLIBS} \
            ${sysconfdir} ${sharedstatedir} ${localstatedir} \
            ${base_libdir}/*${SOLIBS} \
            ${datadir}/${PN} ${libdir}/${PN}/* \
            ${datadir}/pixmaps ${datadir}/applications \
            ${datadir}/idl ${datadir}/omf ${datadir}/sounds \
            ${libdir}/bonobo/servers"

FILES_${PN}-utils = "${bindir}/xmllint* ${bindir}/xmlcatalog* ${libdir}/*.sh"
FILES_${PN}-doc += "${datadir}/gtk-doc"
DEPENDS_${PN}-utils += "libc libm ${DEPENDS_HOST_OS} libxml2"
RDEPENDS_${PN}-utils += "libc libm ${DEPENDS_HOST_OS} libxml2"

#for now this works only with python2
addhook setup_python to post_recipe_parse
def setup_python(d):
    python_version = d.get("PYTHON_VERSION") or ""
    libdir = d.get("libdir") or ""
    major_cmd = "python{} -c 'import sys; print(sys.version_info.major)'".format(python_version)
    minor_cmd = "python{} -c 'import sys; print(sys.version_info.minor)'".format(python_version)
    major = oelite.util.shcmd(major_cmd, quiet=True).strip()
    minor= oelite.util.shcmd(minor_cmd, quiet=True).strip()
    pydir = " {}/python{}.{}".format(libdir, major, minor)
    d.set("PYDIR",pydir.strip())

PYTHONPATH = "${BUILD_SYSROOT}/${PYDIR}"
PYTHONHOME = "${TARGET_SYSROOT}${prefix}"
PYTHONPATH[emit] = "do_configure"
PYTHONHOME[emit] = "do_configure"
PYTHONPATH[export] = "1"
PYTHONHOME[export] = "1"

FILES_${PN}-python += "${PYDIR}/site-packages/libxml2mod.so \
			   ${PYDIR}/site-packages/libxml2.py \
			   ${PYDIR}/site-packages/drv_libxml2.py"
FILES_${PN}-python-dev += "${PYDIR}/site-packages/libxml2mod.la \
			       ${PYDIR}/site-packages/libxml2mod.a"
FILES_${PN}-python-dbg += "${PYDIR}/site-packages/.debug/libxml2mod.so"
