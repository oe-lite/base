inherit pkgconfig cmake c c++

SUMMARY = "Opencv : The Open Computer Vision Library"
HOMEPAGE = "http://opencv.org/"
RECIPE_TYPES = "machine native"
LICENSE = "BSD-3-Clause"

ARM_INSTRUCTION_SET = "arm"

DEPENDS_LIBC = "librt libc"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS += "${DEPENDS_LIBC} libbz2 libz libglib"
SRC_URI = "https://github.com/Itseez/${PN}/archive/${PV}.tar.gz \
  file://0001-Use-__vector-instead-of-vector-as-suggests-Eigen.patch \
  file://0001-cmake-fix-for-GCC-6.x.patch"

EXTRA_OE_CMAKE_CONF += "\
                 -DWITH_GSTREAMER=OFF \
                 -DWITH_1394=OFF \
                 -DCMAKE_SKIP_RPATH=ON \
                 ${@['', '-DENABLE_SSE=1 -DENABLE_SSE2=1 -DENABLE_SSE3=1 -DENABLE_SSSE3=1']['${HOST_FPU}'=='sse']} \
		 -DBUILD_opencv_ts=OFF \
"

DEPENDS += "libjpeg libpng"
EXTRA_OE_CMAKE_CONF += " \
-DWITH_EIGEN=OFF \
-DWITH_GTK=OFF \
-DWITH_JPEG=ON \
-DWITH_FFMPEG=OFF \
-DWITH_PNG=ON \
-DWITH_TIFF=OFF \
-DWITH_V4L=OFF \
-DWITH_JASPER=OFF \
"


PACKAGES += "${PN}-apps"

FILES_${PN} = "${libdir}/libopencv_*"
FILES_${PN}-apps = "${bindir}/* ${datadir}/OpenCV"
FILES_${PN}-dbg += "${libdir}/.debug"
FILES_${PN}-dev = "${libdir}/*.a ${includedir} ${libdir}/pkgconfig"
FILES_${PN}-doc = "${datadir}/OpenCV/doc"

CDEPS = "libdl libgcc libm libpng16 libpthread ${DEPENDS_LIBC} libstdc++"
DEPENDS_${PN} += "${CDEPS} libjpeg libz"
RDEPENDS_${PN} += "${CDEPS} libjpeg libz"
DEPENDS_${PN}-apps += "${CDEPS}"
RDEPENDS_${PN}-apps += "${CDEPS}"
PROVIDES_${PN}[qa] += "allow-missing-provides"
DEPENDS_${PN}[qa] += "allow-missing-lib-depends"
DEPENDS_${PN}-apps[qa] += "allow-missing-lib-depends"
RDEPENDS_${PN}[qa] += "allow-missing-lib-rdepends"
RDEPENDS_${PN}-apps[qa] += "allow-missing-lib-rdepends"


do_configure[postfuncs] += "do_install_fixup"
do_install_fixup() {
    cp ${S}/include/opencv/*.h ${D}${includedir}/opencv/
    sed -i '/blobtrack/d' ${D}${includedir}/opencv/cvaux.h
}

# CMakeLists.txt installs to ${prefix}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/ on mingw
# configuration
FILES_${PN}:>HOST_LIBC_mingw = " /usr/"
