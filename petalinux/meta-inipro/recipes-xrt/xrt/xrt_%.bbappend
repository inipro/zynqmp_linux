FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-Remove-drm.h-and-drm_mode.h.patch"


do_patch () {
	cd ${WORKDIR}/git
	for patch_file in ${WORKDIR}/*.patch; do
		patch -p1 < ${patch_file}
	done
}
