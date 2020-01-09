SRC_URI_append = " \
	file://0001-dnf.conf-no-timeout.patch \
	"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
