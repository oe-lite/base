DESCRIPTION = "Free peer-reviewed portable C++ source libraries"
HOMEPAGE = "http://www.boost.org/"
LICENSE = "Boost Software License"
RECIPE_TYPES = "machine native sdk"
inherit c++ auto-package-libs

require conf/fetch/sourceforge.conf
BOOST_VER = "${@'_'.join(d.get('PV').split('.'))}"
SRC_URI = "${SOURCEFORGE_MIRROR}/boost/boost_${BOOST_VER}.tar.bz2"
S = "${SRCDIR}/boost_${BOOST_VER}"

DEPENDS = "libz libbz2 librt libstdc++ libm libpthread libc libgcc"

# Oh yippee, a new build system, it's sooo cooool I could eat my own
# foot.  inlining=on lets the compiler choose, I think.  At least this
# stuff is documented...
# NOTE: if you leave <debug-symbols>on then in a debug build the build sys
# objcopy will be invoked, and that won't work.  Building debug apparently
# requires hacking gcc-tools.jam
#
# Sometimes I wake up screaming.  Famous figures are gathered in the nightmare,
# Steve Bourne, Larry Wall, the whole of the ANSI C committee.  They're just
# standing there, waiting, but the truely terrifying thing is what they carry
# in their hands.  At first sight each seems to bear the same thing, but it is
# not so for the forms in their grasp are ever so slightly different one from
# the other.  Each is twisted in some grotesque way from the other to make each
# an unspeakable perversion impossible to perceive without the onset of madness.
# True insanity awaits anyone who perceives all of these horrors together.
#
# Quotation marks, there might be an easier way to do this, but I can't find
# it.  The problem is that the user.hpp configuration file must receive a
# pre-processor macro defined as the appropriate string - complete with "'s
# around it.  (<> is a possibility here but the danger to that is that the
# failure case interprets the < and > as shell redirections, creating
# random files in the source tree.)
#
#bjam: '-DBOOST_PLATFORM_CONFIG=\"config\"'
#do_compile: '-sGCC=... '"'-DBOOST_PLATFORM_CONFIG=\"config\"'"
SQD = '"'
EQD = '\"'
#boost.oe:   "...  '-sGCC=... '${SQD}'-DBOOST_PLATFORM_CONFIG=${EQD}config${EQD}'${SQD} ..."
BJAM_CONF = "${SQD}'-DBOOST_PLATFORM_CONFIG=${EQD}boost/config/platform/${TARGET_OS}.hpp${EQD}'${SQD}"

# bzip2 and zip are disabled because... they're broken - the compilation simply
# isn't working with bjam.  I guess they will fix it, but who needs it?  This
# only affects the (new in 33) iostream library.
#		'-sNO_BZIP2=1'
#		'-sNO_ZLIB=1'

BJAM_OPTIONS = "-sTOOLS=gcc"
BJAM_OPTIONS += "'-sGCC=${CC} ${CFLAGS} '${BJAM_CONF}"
BJAM_OPTIONS += "'-sGXX=${CXX} ${CXXFLAGS} '${BJAM_CONF}"
BJAM_OPTIONS += "'-sGCC_INCLUDE_DIRECTORY=${TARGET_SYSROOT}${target_includedir}'"
BJAM_OPTIONS += "'-sGCC_STDLIB_DIRECTORY=${TARGET_SYSROOT}${target_libdir}'"
BJAM_OPTIONS += "'-sBUILD=release <optimization>space <inlining>on <debug-symbols>off'"
BJAM_OPTIONS += "'--layout=system'"

# Generate boost jam compiler options
do_configure[prefuncs] += "boost_flags"
def boost_flags(d):

    cflags = (d.get('CFLAGS') or '').split( )
    boost_cflags = []
    for cflag in cflags:
        boost_cflags.append('<cflags>%s'%(cflag))
    d.set('BJAM_CFLAGS', ' '.join(boost_cflags))

    cxxflags = (d.get('CXXFLAGS') or '').split( )
    boost_cxxflags = []
    for cxxflag in cxxflags:
        boost_cxxflags.append('<cxxflags>%s'%(cxxflag))
    d.set('BJAM_CXXFLAGS', ' '.join(boost_cxxflags))

    ldflags = (d.get('LDFLAGS') or '').split( )
    boost_ldflags = []
    for ldflag in ldflags:
        boost_ldflags.append('<linkflags>%s'%(ldflag))
    d.set('BJAM_LINKFLAGS', ' '.join(boost_ldflags))

# Needs to be defined for early parsing
BJAM_CFLAGS=""
BJAM_CXXFLAGS=""
BJAM_LINKFLAGS=""
do_configure () {
    cp -f boost/config/platform/linux.hpp \
          boost/config/platform/linux-gnueabi.hpp

    (cd ${S}/tools/build/v2/
        if [ ! -f user-config.jam~orig ] ; then
            cp user-config.jam user-config.jam~orig
        fi
        cp user-config.jam~orig user-config.jam
        echo "using gcc : $(${CXX} -dumpversion) : ${CXX} : <define>-DBOOST_SP_USE_PTHREADS ${BJAM_CFLAGS} ${BJAM_CXXFLAGS} ${BJAM_LINKFLAGS} ;" \
            >> user-config.jam
    )
    CC="${BUILD_CC}" CFLAGS="${BUILD_CFLAGS}" ./bootstrap.sh --with-toolset=gcc ${BOOTSTRAP_OPTIONS}
}

do_compile() {
    set -ex
    ./bjam -d2 ${BJAM_OPTIONS} \
    --prefix=${prefix} --exec-prefix=${exec_prefix} \
    --libdir=${libdir} --includedir=${includedir} \
    --debug-configuration
}

do_install() {
    set -ex
    ./bjam ${BJAM_OPTIONS} \
        --libdir=${D}${libdir} --includedir=${D}${includedir} \
        install
}

AUTO_PACKAGE_LIBS = "${BOOST_LIBS}"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:libboost_"
AUTO_PACKAGE_LIBS_PKGPREFIX = ""

BOOST_LIBS += "date_time"

BOOST_LIBS += "filesystem"

BOOST_LIBS += "graph"

BOOST_LIBS += "iostreams"

BOOST_LIBS += "math"
FILES_${PN}-math = "\
    ${libdir}/libboost_math_*${SOLIBS}"
FILES_${PN}-math-dev = "\
    ${libdir}/libboost_math_*${SOLIBSDEV} \
    ${libdir}/libboost_math_*.a"

BOOST_LIBS += "program_options"

BOOST_LIBS += "random"

RECIPE_FLAGS += "boost_icu"
BOOST_LIBS += "regex"
ICU_BOOTSTRAP_OPTION = ""
ICU_BOOTSTRAP_OPTION:USE_boost_icu = "--with-icu"
BOOTSTRAP_OPTIONS += "${ICU_BOOTSTRAP_OPTION}"
ICU_DEPENDS = ""
ICU_DEPENDS:USE_boost_icu += "libicuuc libicui18n libicudata"
DEPENDS += "${ICU_DEPENDS}"
DEPENDS_${PN}-regex-dev = "${ICU_DEPENDS}"

LIBBOST_COMMON_RDEPENDS = "librt libstdc++ libm libpthread libc libgcc"
RDEPENDS_${PN}-regex = "${LIBBOST_COMMON_RDEPENDS} ${ICU_DEPENDS}"
RDEPENDS_${PN}-iostreams = "${LIBBOST_COMMON_RDEPENDS} libz libbz2"
RDEPENDS_${PN}-date-time = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-filesystems = "${LIBBOST_COMMON_RDEPENDS} boost-system"
RDEPENDS_${PN}-graph = "${LIBBOST_COMMON_RDEPENDS} boost-regex"
RDEPENDS_${PN}-math = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-program-options = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-random = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-serialization = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-signals = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-system = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-thread = "${LIBBOST_COMMON_RDEPENDS}"
RDEPENDS_${PN}-wave = "${LIBBOST_COMMON_RDEPENDS} boost-date-time boost-thread boost-filesystem boost-system"
RDEPENDS_${PN}-wserialization = "${LIBBOST_COMMON_RDEPENDS} boost-serialization"

BOOST_LIBS += "serialization"
FILES_${PN}-serialization = "\
    ${libdir}/libboost_wserialization${SOLIBSDEV}"
FILES_${PN}-serialization-dev = "\
    ${libdir}/libboost_wserialization${SOLIBS} \
    ${libdir}/libboost_wserialization.a"

BOOST_LIBS += "signals"

BOOST_LIBS += "system"

BOOST_LIBS += "thread"

BOOST_LIBS += "wave"

BOOST_LIBS += "test"
FILES_${PN}-test = "\
    ${libdir}/libboost_prg_exec_monitor${SOLIBS} \
    ${libdir}/libboost_test_exec_monitor${SOLIBS} \
    ${libdir}/libboost_unit_test_framework${SOLIBS}"
FILES_${PN}-test-dev = "\
    ${libdir}/libboost_prg_exec_monitor${SOLIBSDEV} \
    ${libdir}/libboost_prg_exec_monitor.a \
    ${libdir}/libboost_test_exec_monitor${SOLIBSDEV} \
    ${libdir}/libboost_test_exec_monitor.a \
    ${libdir}/libboost_unit_test_framework${SOLIBSDEV} \
    ${libdir}/libboost_unit_test_framework.a"

# To enable python, do something like the above, and more....
#BOOST_LIBS += "python"
#DEPENDS += "python"
#PYTHON_ROOT = "${STAGING_DIR_HOST}/${layout_prefix}"
#PYTHON_VERSION = "2.5"
#BOOTSTRAP_OPTIONS += "--with-python-root=${PYTHON_ROOT}"
#BJAM_OPTIONS += "'-sPYTHON_VERSION=${PYTHON_VERSION}'"

BOOTSTRAP_OPTIONS += "--with-libraries=${@','.join('${BOOST_LIBS}'.split())}"
