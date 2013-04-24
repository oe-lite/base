DESCRIPTION = "GNU multiprecision arithmetic library"
HOMEPAGE = "http://www.swox.com/gmp/"

RECIPE_TYPES = "machine native sdk"
inherit autotools 

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gmp/gmp-${PV}.tar.gz;name=gmp"

export CC_FOR_BUILD="${BUILD_CC}"

ARM_INSTRUCTION_SET = "arm"

EXTRA_OECONF:>native = " --enable-static"

acpaths = ""
