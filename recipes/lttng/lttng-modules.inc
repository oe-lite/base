# -*- mode:python; -*-
DESCRIPTION = "LTTng 2.0 kernel modules"
LICENSE = "LGPLv2.1 GPLv2 MIT"

RECIPE_TYPES = "machine"

inherit kernel-modules
KERNEL_MODULES_COMPILE_MAKE_TARGETS = "default"

SRC_URI = "http://lttng.org/files/lttng-modules/lttng-modules-${PV}.tar.bz2"

KERNEL_MAKEFILE = "${STAGE_DIR}/${HOST_TYPE}${kernelsrcdir}/Makefile"
KERNEL_EVENTS_SUBDIR = "${STAGE_DIR}/${HOST_TYPE}${kernelsrcdir}/include/trace/events"

addtask instrumentation after patch stage before configure
do_instrumentation[dirs] = "${S}"
def do_instrumentation(d):
    with open(d.get("KERNEL_MAKEFILE")) as makefile:
        version = {
            "VERSION" : None,
            "PATCHLEVEL" : None,
            "SUBLEVEL" : None,
            "EXTRAVERSION" : None
            }
        for line in makefile:
            all_defined = True
            for (var, value) in version.items():
                v = re.match(r"%s\s*=\s*(\S*)"%(var), line)
                if v:
                    version[var] = v.group(1)
                else:
                    if value is None:
                        all_defined = False
            if all_defined:
                break
    if not all_defined:
        bb.error("Cannot determine kernel version from Makefile")
        return False
    v = version["VERSION"] + "." + version["PATCHLEVEL"]
    if int(version["VERSION"]) < 3:
        v += "." + version["SUBLEVEL"]
    patchfile = os.path.join(
        d.get("SRCDIR"), "instrumentation-events-%s.patch"%(v))
    print "using patchfile:%s"%patchfile
    if not os.path.exists(patchfile):
        bb.error("Cannot find instrumentation patch file:", patchfile)
        return False
    try:
        os.chdir(os.path.join(d.get("S"), "instrumentation", "events"))
    except OSError, e:
        bb.error("Cannot find instrumentation/events subdir")
        print e
        print "cwd is", os.getcwd()
        return False
    try:
        shutil.move("lttng-module", "lttng-module~orig")
    except OSError, e:
        bb.error("Cannot rename lttng-module subdir")
        print e
        return False
    os.mkdir("lttng-module")
    files = os.listdir("mainline")
    mainline_dir = d.get("KERNEL_EVENTS_SUBDIR")
    os.chdir("lttng-module")
    for f in files:
        src = os.path.join(mainline_dir, f)
        shutil.copyfile(src, f)
    rc = os.system("patch -p1 -i %s"%(patchfile))
    if rc != 0:
        bb.error("Patching instrumentation/events subdir failed")
        return False

PACKAGES = "${PN}"
FILES_${PN} = "/lib/modules"
