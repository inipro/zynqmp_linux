FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append_ultra96-zynqmp = " \
    ${@bb.utils.contains('ULTRA96_VERSION', '2', 'file://0001-ultra96-v2-ap-config.patch', '', d)} \
    ${@bb.utils.contains('ULTRA96_VERSION', '2', 'file://0002-ultra96-v2-udhcpd-config.patch', '', d)} \
"

