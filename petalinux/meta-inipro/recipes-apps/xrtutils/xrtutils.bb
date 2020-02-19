SUMMARY = "xrtutils library"
SECTION = "PETALINUX/libs"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://*"

S = "${WORKDIR}"

inherit cmake

FILES_${PN}-dev += "${datadir}/xrtutils/cmake"

DEPENDS = "xrt"
RDEPENDS_${PN}-dev = "xrt"
