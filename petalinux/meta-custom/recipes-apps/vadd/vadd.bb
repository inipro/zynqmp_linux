LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://CMakeLists.txt \
		   file://main.cpp \
		   file://xvadd_hw.h \
		   file://xvadd.h \
		   file://xvadd.c \
		   file://xvadd_linux.c \
		  "

S = "${WORKDIR}"

DEPENDS = "zocl"

inherit cmake

EXTRA_OECMAKE = ""

