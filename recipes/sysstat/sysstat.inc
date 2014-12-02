DESCRIPTION = "The sysstat utilities are a collection of performance monitoring tools for Linux."
HOMEPAGE = "http://pagesperso-orange.fr/sebastien.godard/"
LICENSE = "GPL"

SRC_URI = "http://pagesperso-orange.fr/sebastien.godard/sysstat-${PV}.tar.bz2"

inherit autotools

EXTRA_OECONF += "--disable-documentation"

# package /var/log only in debug
FILES_${PN} += "${libdir}/sa"
FILES_${PN}-dbg += "${localstatedir}"
