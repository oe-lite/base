inherit autotools pkgconfig library

RECIPE_TYPES = "machine sdk"

DESCRIPTION = "Sodium is a modern, easy-to-use software library for encryption, decryption, signatures, password hashing and more."
HOMEPAGE = "https://download.libsodium.org/doc/"
LICENSE = "ISC"

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"

# libsodium places DEF files in bindir instead of libdir, and I am not sure
# what is the right location, or if both are acceptable, so I guess I can
# just as well leave it as-is.
FILES_DEV_MINGW:HOST_OS_mingw32 += "${bindir}/*.def"
