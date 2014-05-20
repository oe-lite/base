SUMMARY = "File is a utility that classifies arbitrary files of any type mainly by their contents."
DESCRIPTION = ""
HOMEPAGE = "http://freecode.com/projects/file"
LICENSE = "BSD"

RECIPE_TYPES = "native machine"
DEPENDS:>machine += " native:file"

SRC_URI = "ftp://ftp.astron.com/pub/file/file-${PV}.tar.gz"

FILES_${PN} += "${datadir}/misc/magic.mgc"

inherit autotools
