FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-Remove-drm.h-and-drm_mode.h.patch"

FILES_${PN}-dev += "${includedir}/zocl/*"

do_patch () {
	cd ${WORKDIR}/git
	for patch_file in ${WORKDIR}/*.patch; do
		patch -p1 < ${patch_file}
	done
}

do_install_append () {
	install -d ${D}${includedir}/zocl
	install -m 0644 ${S}/../../include/zynq_ioctl.h ${D}${includedir}/zocl
}
