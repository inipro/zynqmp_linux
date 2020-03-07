FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://miniterm.py"

do_install_append () {
	install -m 0755 ${WORKDIR}/miniterm.py ${D}${bindir}
}
