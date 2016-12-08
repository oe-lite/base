SUMMARY = "sg3_utils is a set of utilities that send SCSI commands to devices"
HOMEPAGE = "http://sg.danny.cz/sg/sg3_utils.html"
LICENSE = "BSD-3-Clause"

SRC_URI = "http://sg.danny.cz/sg/p/sg3_utils-${PV}.tar.xz"

RECIPE_TYPES = "machine native"

S = "${SRCDIR}/sg3_utils-${PV}"

inherit autotools
inherit auto-package-libs

DEPENDS += "libpthread"

AUTO_PACKAGE_LIBS = "sgutils2"
AUTO_PACKAGE_LIBS_DEPENDS = "libc libpthread"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libpthread"
LIBRARY_VERSION = "2"

inherit auto-package-utils

AUTO_PACKAGE_UTILS_DEPENDS += "libsgutils2"
AUTO_PACKAGE_UTILS_RDEPENDS += "libsgutils2"

# Generated with "ls -1 install/usr/bin"
AUTO_PACKAGE_UTILS = """
scsi_logging_level
scsi_mandat
scsi_readcap
scsi_ready
scsi_satl
scsi_start
scsi_stop
scsi_temperature
sg_compare_and_write
sg_copy_results
sg_dd
sg_decode_sense
sg_emc_trespass
sg_format
sg_get_config
sg_get_lba_status
sg_ident
sg_inq
sg_logs
sg_luns
sg_map
sg_map26
sg_modes
sg_opcodes
sg_persist
sg_prevent
sg_raw
sg_rbuf
sg_rdac
sg_read
sg_read_attr
sg_read_block_limits
sg_read_buffer
sg_read_long
sg_readcap
sg_reassign
sg_referrals
sg_rep_zones
sg_requests
sg_reset
sg_reset_wp
sg_rmsn
sg_rtpg
sg_safte
sg_sanitize
sg_sat_identify
sg_sat_phy_event
sg_sat_read_gplog
sg_sat_set_features
sg_scan
sg_senddiag
sg_ses
sg_ses_microcode
sg_start
sg_stpg
sg_sync
sg_test_rwbuf
sg_timestamp
sg_turs
sg_unmap
sg_verify
sg_vpd
sg_wr_mode
sg_write_buffer
sg_write_long
sg_write_same
sg_write_verify
sg_xcopy
sg_zone
sginfo
sgm_dd
sgp_dd
"""
