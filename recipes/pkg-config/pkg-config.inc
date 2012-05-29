# -*- mode:python; -*-
DESCRIPTION = "pkg-config is a system for managing library \
compile/link flags that works with automake and autoconf. \
It replaces the ubiquitous *-config scripts you may have \
seen with a single tool."
HOMEPAGE = "http://pkg-config.freedesktop.org/wiki/"

RECIPE_TYPES = "machine native sdk"

inherit autotools-autoreconf pkgconfig

DEPENDS = "libdl libpthread libglib"

SRC_URI = "http://pkgconfig.freedesktop.org/releases/pkg-config-${PV}.tar.gz"

SRC_URI += "file://common.site file://host_cpu.site"
SRC_HOST_SITEFILES = "${SRCDIR}/common.site ${SRCDIR}/host_cpu.site"

acpaths = "-I ."

EXTRA_OECONF = "--with-pc-path=''"

do_install() {
	do_install_make
	install -d -m 0755 ${D}${libdir}/pkgconfig
}

# We have to rely on host provided pkg-config, which might not have sysroot
# support, so we need to mangle .pc files instead.
PKGCONFIG_DEPENDS:native = ""
PKG_CONFIG_SYSROOT_DIR:native = ""

PCFILE_MANGLE_GLOB = "${libdir}/pkgconfig/*.pc"
PCFILE_MANGLE_PATHVARS = "prefix exec_prefix libdir includedir"
PCFILE_MANGLE_SYSROOT = "${STAGE_DIR}/native"

do_stage[postfuncs] += "${DO_STAGE_PCFILE_MANGLE}"
DO_STAGE_PCFILE_MANGLE:native = "do_stage_pcfile_mangle"
def do_stage_pcfile_mangle(d):
    pathvars = d.get("PCFILE_MANGLE_PATHVARS").split()
    sysroot = d.get("PCFILE_MANGLE_SYSROOT")
    print "globbing %s"%(sysroot + d.get("PCFILE_MANGLE_GLOB"))
    for pcfilename in glob.glob(sysroot + d.get("PCFILE_MANGLE_GLOB")):
        print "pcfile", pcfilename
        with open(pcfilename) as _pcfile:
            pcfile = _pcfile.read()
        print "replacing %r"%(r"(^|\n)(%s)="%("|".join(pathvars)))
        pcfile = re.sub(r"(^|\n)(%s)="%("|".join(pathvars)),
                        r"\1\2=%s"%(sysroot), pcfile, re.MULTILINE)
        with open(pcfilename, "w") as _pcfile:
            _pcfile.write(pcfile)
