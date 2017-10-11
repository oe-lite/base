LICENSE = "ISC"
COMPATIBLE_HOST_ARCHS = "arm- x86_64-"

inherit c make

CFLAGS += "-g"

RECIPE_FLAGS += "skaware_extra_cflags"
CFLAGS:>USE_skaware_extra_cflags = " ${USE_skaware_extra_cflags}"
