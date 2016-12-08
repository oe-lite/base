SUMMARY = "libssh is a library written in C implementing the SSH protocol"
LICENSE = "LGPL-2.1"
SRC_URI = "https://red.libssh.org/attachments/download/195/libssh-${PV}.tar.xz"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine native"

inherit cmake c++
inherit library auto-package-libs

libdeps = "libc libm libz libssl libpthread libcrypto libutil libstdc++"
DEPENDS += "${libdeps}"
DEPENDS_${PN} += "${libdeps}"
RDEPENDS_${PN} += "${libdeps}"

AUTO_PACKAGE_LIBS = "ssh_threads"
AUTO_PACKAGE_LIBS_DEPENDS += "libpthread libssh"
AUTO_PACKAGE_LIBS_RDEPENDS += "libpthread libssh"

FILES_${PN}-dev += "${libdir}/cmake/${PN}"

PACKAGES =+ "${PN}-examples"
EXAMPLES = "        \
  exec              \
  libsshpp          \
  libsshpp_noexcept \
  libssh_scp        \
  samplesftp        \
  samplessh         \
  samplesshd-kbdint \
  scp_download      \
  senddata          \
  sshnetcat         \
  ssh_server_fork   \
"
do_install_examples() {
  install -d -m 0755 ${D}${bindir}/${PN}
  for x in ${EXAMPLES} ; do
    install -m 0755 ${B}/examples/$x ${D}${bindir}/${PN}
  done
}
do_install[postfuncs] =+ "do_install_examples"
FILES_${PN}-examples += "${bindir}/${PN}"
FILES_${PN}-examples[qa] += 'allow-elf-bins-in-other-dirs'
DEPENDS_${PN}-examples += "libssh libgcc"
RDEPENDS_${PN}-examples += "libssh libgcc"
CHRPATH_DIRS += "${bindir}/${PN}"
