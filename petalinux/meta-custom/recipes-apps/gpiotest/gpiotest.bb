LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://CMakeLists.txt \
		   file://main.c \
		   file://gpio_utils.h \
		   file://gpio_utils.c \
		   "

S = "${WORKDIR}"

inherit cmake

EXTRA_OECMAKE = ""

