DESCRIPTION = "Free peer-reviewed portable C++ source libraries"
HOMEPAGE = "http://www.boost.org/"
LICENSE = "Boost Software License"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

inherit c++ auto-package-libs

require conf/fetch/sourceforge.conf
BOOST_VER = "${@'_'.join(d.get('PV').split('.'))}"
SRC_URI = "${SOURCEFORGE_MIRROR}/boost/boost_${BOOST_VER}.tar.bz2"
S = "${SRCDIR}/boost_${BOOST_VER}"

DEPENDS_LIBC = "librt libpthread"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS = "${DEPENDS_LIBC} libz libbz2 libstdc++ libm libc libgcc"

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
BJAM_OPTIONS += "'-sGCC=${CC} ${CPPFLAGS} ${CFLAGS} '${BJAM_CONF}"
BJAM_OPTIONS += "'-sGXX=${CXX} ${CPPFLAGS} ${CXXFLAGS} '${BJAM_CONF}"
BJAM_OPTIONS += "'-sGCC_INCLUDE_DIRECTORY=${TARGET_SYSROOT}${target_includedir}'"
BJAM_OPTIONS += "'-sGCC_STDLIB_DIRECTORY=${TARGET_SYSROOT}${target_libdir}'"
BJAM_OPTIONS += "'-sBUILD=release <optimization>space <inlining>on <debug-symbols>off'"
BJAM_OPTIONS += "'--layout=system'"

# Generate boost jam compiler options
do_configure[prefuncs] += "boost_flags"
def boost_flags(d):
    cppflags = (d.get('CPPFLAGS') or '').split( )

    cflags = (d.get('CFLAGS') or '').split( )
    boost_cflags = []
    for cflag in cppflags + cflags:
        boost_cflags.append('<cflags>%s'%(cflag))
    d.set('BJAM_CFLAGS', ' '.join(boost_cflags))

    cxxflags = (d.get('CXXFLAGS') or '').split( )
    boost_cxxflags = []
    for cxxflag in cppflags + cxxflags:
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
    CC="${BUILD_CC}" CFLAGS="${BUILD_CFLAGS}" CPPFLAGS="${BUILD_CFLAGS}" CXXFLAGS="${BUILD_CFLAGS}" ./bootstrap.sh --with-toolset=gcc ${BOOTSTRAP_OPTIONS}
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

BOOST_LIBS = "\
	chrono date_time filesystem graph iostreams math \
	program_options random regex serialization signals system \
	thread test wave"
AUTO_PACKAGE_LIBS = "\
	boost_chrono boost_date_time boost_filesystem boost_graph \
	boost_iostreams boost_math_c99f boost_math_c99l boost_math_c99 \
	boost_math_tr1f boost_math_tr1l boost_math_tr1 boost_prg_exec_monitor \
	boost_program_options boost_random boost_regex boost_serialization \
	boost_signals boost_system boost_thread boost_unit_test_framework \
	boost_wave boost_wserialization"

RECIPE_FLAGS += "boost_icu"
ICU_BOOTSTRAP_OPTION = ""
ICU_BOOTSTRAP_OPTION:USE_boost_icu = "--with-icu"
BOOTSTRAP_OPTIONS += "${ICU_BOOTSTRAP_OPTION}"
ICU_DEPENDS = ""
ICU_DEPENDS:USE_boost_icu += "libicuuc libicui18n libicudata"

LIBBOOST_COMMON_RDEPENDS = "librt libstdc++ libm libpthread libc libgcc"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "${LIBBOOST_COMMON_RDEPENDS}"
AUTO_PACKAGE_LIBS_RDEPENDS += "${LIBBOOST_COMMON_RDEPENDS}"

DEPENDS_${PN}-libboost-chrono += "libboost-system"
RDEPENDS_${PN}-libboost-chrono += "libboost-system"
DEPENDS_${PN}-libboost-filesystem += "libboost-system"
RDEPENDS_${PN}-libboost-filesystem += "libboost-system"
DEPENDS_${PN}-libboost-thread += "libboost-system"
RDEPENDS_${PN}-libboost-thread += "libboost-system"
DEPENDS_${PN}-libboost-graph += "libboost-regex"
RDEPENDS_${PN}-libboost-graph += "libboost-regex"
DEPENDS_${PN}-libboost-iostreams += "libbz2 libz"
RDEPENDS_${PN}-libboost-iostreams += "libbz2 libz"
DEPENDS_${PN}-libboost-wave += "libboost-chrono libboost-date-time \
			libboost-filesystem libboost-system libboost-thread"
RDEPENDS_${PN}-libboost-wave += "libboost-chrono libboost-date-time \
			libboost-filesystem libboost-system libboost-thread"
DEPENDS_${PN}-libboost-wserialization += "libboost-serialization"
RDEPENDS_${PN}-libboost-wserialization += "libboost-serialization"

BOOTSTRAP_OPTIONS += "--with-libraries=${@','.join('${BOOST_LIBS}'.split())}"

#Ensure no libraries are placed in PN
FILES_${PN} = ""
