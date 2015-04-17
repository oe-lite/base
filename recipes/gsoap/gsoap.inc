DESCRIPTION = "The gSOAP toolkit provides a unique SOAP-to-C/C++ language binding \
for the development of SOAP Web Services and clients."
SECTION = "devel"
LICENSE = "GPL"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/gsoap2/gSOAP/gsoap_${PV}.zip"

inherit autotools-autoreconf c++

S = "${SRCDIR}/gsoap-2.8"

# :(
PARALLEL_MAKE = ""

EXTRA_OEMAKE = "SOAP=${STAGE_DIR}/native/bin/soapcpp2"
