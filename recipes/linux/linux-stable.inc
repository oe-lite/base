# -*- mode:python; -*-

FILESPATHPKG = "${P}:${PN}-${@'.'.join('${PV}'.split('.')[:2])}:${PN}:files"

require conf/fetch/kernelorg.conf
SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git;tag=v${PV}"
SRC_URI .= ";repo=linux.git"
S = "${SRCDIR}/linux-stable"

# Include linux-MAJOR.MINOR.inc
include linux-${@'.'.join('${PV}'.split('.')[:2])}.inc
