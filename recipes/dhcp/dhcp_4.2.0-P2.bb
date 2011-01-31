require dhcp4.inc

SRC_URI += "file://fix-external-bind.patch"
SRC_URI += "file://nobash.patch"

#SRC_URI += "file://fixincludes.patch \
#            file://dhcp-3.0.3-dhclient-dbus.patch;striplevel=0 \
#            file://fix-client-path.patch \
#            file://fix-external-bind.patch \
#           "
