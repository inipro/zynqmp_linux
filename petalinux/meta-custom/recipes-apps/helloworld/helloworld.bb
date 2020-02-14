LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://CMakeLists.txt file://main.c"

S = "${WORKDIR}"

inherit cmake

EXTRA_OECMAKE = ""

