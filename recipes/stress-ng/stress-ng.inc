SUMMARY = "stress-ng tests a system by stressing the physical and kernel interfaces."

DESCRIPTION = "stress-ng will stress test a computer system in various selectable ways. It was designed to exercise various physical subsystems of a computer as well as the various operating system kernel interfaces."

LICENSE = "GPL-2.0+"
HOMEPAGE = "http://kernel.ubuntu.com/~cking/stress-ng/"

SRC_URI = "http://kernel.ubuntu.com/~cking/tarballs/stress-ng/stress-ng-${PV}.tar.gz"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make

DEPS = "libm"

# stress-ng is configured entirely by what is available at build
# time. So we make USE flags for each piece that we may want to stage.
DEPENDS += "${DEPS}"
DEPENDS_${PN} = "${DEPS}"
RDEPENDS_${PN} = "${DEPS}"

# libcrypt, librt and libz are in all likelyhood already included in
# the rootfs, so enable those by default.
RECIPE_FLAGS += "stressng_crypt"
DEFAULT_USE_stressng_crypt = True
DEPS:>USE_stressng_crypt = " libcrypt"

RECIPE_FLAGS += "stressng_rt"
DEFAULT_USE_stressng_rt = True
DEPS:>USE_stressng_rt = " librt"

RECIPE_FLAGS += "stressng_z"
DEFAULT_USE_stressng_z = True
DEPS:>USE_stressng_z = " libz"

# libcap requires opt-in.
RECIPE_FLAGS += "stressng_cap"
DEFAULT_USE_stressng_cap = False
DEPS:>USE_stressng_cap = " libcap"

# There are no upstream recipes for these, so enabling these requires
# some additional work.
RECIPE_FLAGS += "stressng_sctp"
DEFAULT_USE_stressng_sctp = False
DEPS:>USE_stressng_sctp = " libsctp"

RECIPE_FLAGS += "stressng_aio"
DEFAULT_USE_stressng_aio = False
DEPS:>USE_stressng_aio = " libaio"

RECIPE_FLAGS += "stressng_bsd"
DEFAULT_USE_stressng_bsd = False
DEPS:>USE_stressng_bsd = " libbsd"
