require ntp.inc

SRC_URI += "\
    file://ntp-4.2.4_p6-nano.patch;patch=1 \
    file://tickadj.c.patch;patch=1 \
    file://tv_nsec-instead-of-tv_usec.patch;patch=1 \
"
