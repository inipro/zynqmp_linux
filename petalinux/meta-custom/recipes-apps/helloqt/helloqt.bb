LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://CMakeLists.txt \
		   file://main.cpp \
		   file://main.qml \
		   file://qml.qrc \
"

S = "${WORKDIR}"

DEPENDS = "qtdeclarative qtgraphicaleffects"

inherit cmake cmake_qt5

EXTRA_OECMAKE = ""
