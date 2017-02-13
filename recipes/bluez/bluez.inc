DESCRIPTION = "Official Linux Bluetooth protocol stack"
HOMEPAGE = "http://www.bluez.org/"
LICENSE = "GPL-2.0"

RECIPE_TYPES = "machine"
RECIPE_FLAGS += "bluez-client"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make autotools auto-package-libs auto-package-utils pkgconfig

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/linux/bluetooth/${P}.tar.xz"

BLUEZ_CLIENT = "--disable-client"
BLUEZ_CLIENT:USE_bluez-client = "--enable-client"
BLUEZ_CLIENT_DEP = ""
BLUEZ_CLIENT_DEP:USE_bluez-client = "libreadline"

EXTRA_OECONF += "--disable-obex "
EXTRA_OECONF += "--disable-systemd"
EXTRA_OECONF += "--disable-cups"
EXTRA_OECONF += "--enable-library"
EXTRA_OECONF += "--enable-tools"
EXTRA_OECONF += "--enable-manpages"
EXTRA_OECONF += "--enable-datafiles"
EXTRA_OECONF += "--disable-experimental"
EXTRA_OECONF += "--disable-android"
EXTRA_OECONF += "--disable-test"
EXTRA_OECONF += "--disable-debug"
EXTRA_OECONF += "--disable-udev"
EXTRA_OECONF += "--disable-threads"
EXTRA_OECONF += "${BLUEZ_CLIENT}"

DEPENDS="libc libdbus-1 libdl libglib-2.0 librt ${BLUEZ_CLIENT_DEP}"
DEPENDS_${PN}="libc libdbus-1 libdl libglib-2.0 librt"
RDEPENDS_${PN}="libc libdbus-1 libdl libglib-2.0 librt ${BLUEZ_CLIENT_DEP}"

AUTO_PACKAGE_UTILS=" \
l2ping \
sdptool \
rctest \
hex2hcd \
l2test \
btmon \
rfcomm \
bluemoon \
hciattach \
mpris-proxy \
bccmd \
hcitool \
hciconfig \
hcidump \
ciptool \
bluetoothd \
obexd \
"
AUTO_PACKAGE_UTILS:>USE_bluez-client += " bluetoothctl"

DEPENDS_${PN}-l2ping = "libc"
RDEPENDS_${PN}-l2ping = "libc"
DEPENDS_${PN}-sdptool = "libc libglib-2.0"
RDEPENDS_${PN}-sdptool="libc libglib-2.0"
DEPENDS_${PN}-rctest = "libc"
RDEPENDS_${PN}-rctest = "libc"
DEPENDS_${PN}-hex2hcd = "libc"
RDEPENDS_${PN}-hex2hcd = "libc"
DEPENDS_${PN}-l2test = "libc"
RDEPENDS_${PN}-l2test = "libc"
DEPENDS_${PN}-btmon = "libc"
RDEPENDS_${PN}-btmon = "libc"
DEPENDS_${PN}-rfcomm = "libc"
RDEPENDS_${PN}-rfcomm = "libc"
DEPENDS_${PN}-bluemoon = "libc"
RDEPENDS_${PN}-bluemoon = "libc"
DEPENDS_${PN}-hciattach = "libc"
RDEPENDS_${PN}-hciattach = "libc"
DEPENDS_${PN}-mpris-proxy = "libc libdbus libdbus-1 libglib-2.0"
RDEPENDS_${PN}-mpris-proxy = "libc libdbus libdbus-1 libglib-2.0"
DEPENDS_${PN}-bccmd = "libc"
RDEPENDS_${PN}-bccmd = "libc"
DEPENDS_${PN}-hcitool = "libc"
RDEPENDS_${PN}-hcitool = "libc"
DEPENDS_${PN}-hciconfig = "libc"
RDEPENDS_${PN}-hciconfig = "libc"
DEPENDS_${PN}-hcidump = "libc"
RDEPENDS_${PN}-hcidump = "libc"
DEPENDS_${PN}-ciptool = "libc"
RDEPENDS_${PN}-ciptool = "libc"
DEPENDS_${PN}-bluetoothd = "libc"
RDEPENDS_${PN}-bluetoothd = "libc"
FILES_${PN}-obexd += "${libexecdir}/bluetooth/obexd"
FILES_${PN}-bluetoothd += "${libexecdir}/bluetooth/bluetoothd"
DEPENDS_${PN}-bluetoothctl += "libglib-2.0 libdbus-1 libreadline libc"
RDEPENDS_${PN}-bluetoothctl += "libglib-2.0 libdbus-1 libreadline libc"

FILES_bluez[qa] += "allow-bin-rel-rpath"
FILES_bluez[qa] += "allow-bin-abs-rpath"
FILES_bluez[qa] += "allow-elf-bins-in-other-dirs"

AUTO_PACKAGE_LIBS="\
bluetooth \
"
PROVIDES_${PN}-libbluetooth = "libbluetooth libbluetooth-3"
DEPENDS_${PN}-libbluetooth = "libc"
RDEPENDS_${PN}-libbluetooth = "libc"
