FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "${@bb.utils.contains('ULTRA96_VERSION', '2', 'file://0001-Patch-the-kernel-to-manipulate-the-wifi-part-s-pins.patch', '', d)} \
file://0001-ov5640-for-digilent-pcam5c.patch \
"
