# -*- mode:python; -*-

require conf/fetch/kernelorg.conf
SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git;tag=v${PV}"
SRC_URI .= ";repo=linux.git"
S = "${SRCDIR}/linux"

# Include linux-MAJOR.MINOR.inc
require linux-${@'.'.join('${PV}'.split('.')[:2])}.inc
