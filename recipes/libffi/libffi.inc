# -*- mode:python; -*-
SUMMARY = "A portable foreign function interface library"
DESCRIPTION = """The libffi library provides a portable, high level
programming interface to various calling conventions.  This allows a
programmer to call any function specified by a call interface
description at run time. FFI stands for Foreign Function Interface.  A
foreign function interface is the popular name for the interface that
allows code written in one language to call code written in another
language.  The libffi library really only provides the lowest, machine
dependent layer of a fully featured foreign function interface.  A
layer must exist above libffi that handles type conversions for values
passed between the two languages."""

RECIPE_TYPES = "machine native sdk"

inherit library autotools c++

SRC_URI = "ftp://sourceware.org/pub/libffi/${PN}-${PV}.tar.gz"

COMMON_DEPENDS = "libc libgcc"
DEPENDS_${PN} += "${COMMON_DEPENDS}"
RDEPENDS_${PN} += "${COMMON_DEPENDS}"
