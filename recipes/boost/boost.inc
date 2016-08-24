DESCRIPTION = "Free peer-reviewed portable C++ source libraries"
HOMEPAGE = "http://www.boost.org/"
LICENSE = "BSL-1.0"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"
# Adding support for Windows requires target-os being configured below

inherit c++ auto-package-libs

require conf/fetch/sourceforge.conf
BOOST_VER = "${@'_'.join(d.get('PV').split('.'))}"
SRC_URI = "${SOURCEFORGE_MIRROR}/boost/boost_${BOOST_VER}.tar.bz2"
S = "${SRCDIR}/boost_${BOOST_VER}"

DEPENDS_LIBC = "librt libpthread"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS = "${DEPENDS_LIBC} libz libbz2 libstdc++ libm libc libgcc"

# inlining=on lets the compiler choose, I think.  At least this
# stuff is documented...
# NOTE: if you leave <debug-symbols>on then in a debug build the build sys
# objcopy will be invoked, and that won't work.  Building debug apparently
# requires hacking gcc-tools.jam

# http://www.boost.org/build/doc/html/bbv2/tasks/crosscompile.html
# file: user-config.jam
# action: add line at end using ${CXX} from OE-lite env like
#   using gcc : arm : arm-none-linux-gnueabi-g++ ;
# b2 toolset=gcc-arm <target-os=linux>
#   target-os only needed if cross compiling on windows os for linux on arm
# b2 name as of version 1.47, oe-lite usage as of 1.59
# Shell Quoting: Add one \ for each nested parser handling the line - roughly
BJAM_CONF = "\'-DBOOST_PLATFORM_CONFIG=\\"boost/config/platform/${TARGET_OS}.hpp\\"\'"

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

# Setup boost support for cross compilation:
#  Not in boost documentation (1.59.0)
#    ensure user-config.jam is placed properly
#    naming convention and location of linux.hpp
do_configure () {
    cp -f boost/config/platform/linux.hpp \
          boost/config/platform/linux-gnueabi.hpp

    (cd ${S}/tools/build/

    cp example/user-config.jam src/user-config.jam
    echo "using gcc : $(${CXX} -dumpversion) : ${CXX} : <define>-DBOOST_SP_USE_PTHREADS ${BJAM_CFLAGS} ${BJAM_CXXFLAGS} ${BJAM_LINKFLAGS} ;" \
        >> src/user-config.jam
    )
    CC="${BUILD_CC}" CFLAGS="${BUILD_CFLAGS}" CPPFLAGS="${BUILD_CFLAGS}" CXXFLAGS="${BUILD_CFLAGS}" ./bootstrap.sh --with-toolset=gcc ${BOOTSTRAP_OPTIONS}
}

do_compile() {
    set -ex
    ./b2 -d2 ${BJAM_OPTIONS} \
    --prefix=${prefix} --exec-prefix=${exec_prefix} \
    --libdir=${libdir} --includedir=${includedir} \
    --debug-configuration ${PARALLEL_MAKE}
}

do_install() {
    # Install headers and libs to install/usr/include/boost install/lib/
    # For target only libs are wanted, (boost)
    # For sdk both are requested       (boost-dev)
    set -ex
    ./b2 ${BJAM_OPTIONS} \
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
DEPENDS_${PN}-libboost-prg-exec-monitor += "libboost-system libboost-timer"
RDEPENDS_${PN}-libboost-prg-exec-monitor += "libboost-system libboost-timer"

DEPENDS_${PN}-libboost-unit-test-framework += "libboost-system libboost-timer"
RDEPENDS_${PN}-libboost-unit-test-framework += "libboost-system libboost-timer"

BOOTSTRAP_OPTIONS += "--with-libraries=${@','.join('${BOOST_LIBS}'.split())}"

#Ensure no libraries are placed in PN
FILES_${PN} = ""

LIBRARY_VERSION = "1"

#make it possible to get all of boost easily
PACKAGES += "${PN}-full ${PN}-full-dev"
RDEPENDS_${PN}-full += "${LIBS_AUTO_RPACKAGES}"
addhook add_deps to post_recipe_parse after auto_package_libs before blacklist
do_fetch[prefuncs] += "add_deps"
def add_deps(d):
    pn = (d.get('PN') or '')
    rdeps = (d.get('LIBS_AUTO_RPACKAGES') or '').split( )
    rdepsdev = []
    for lib in rdeps:
        rdepsdev.append(lib+"-dev")
    #boost-dev contains all the boost header-only code
    rdepsdev.append(pn+"-dev")
    d.set('RDEPENDS_boost-full-dev', ' '.join(rdepsdev))
