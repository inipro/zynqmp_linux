#
# This file is the vai recipe.
#

SUMMARY = "Vitis AI Libraries"
SECTION = "libs"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit python3native

SRC_URI = " \
	file://bin/ddump \
	file://bin/dexplorer \
	file://bin/dsight \
	file://include/dnndk/dnndk.h \
	file://include/dnndk/n2cube.h \
	file://include/vai/dpu_runner.hpp \
	file://include/vai/runner.hpp \
	file://include/vai/tensor_buffer.hpp \
	file://include/vai/tensor.hpp \
	file://include/vai/xdpurunner.h \
	file://lib/echarts.js \
	file://lib/libdpuaol.so \
	file://lib/libdsight.a \
	file://lib/libhineon.so \
	file://lib/libn2cube.so \
	file://python/Edge_Vitis_AI-1.0-py2.py3-none-any.whl \
"

S = "${WORKDIR}"

do_install () {
	install -d ${D}/usr/bin
	install -m 0755 ${S}/bin/* ${D}/usr/bin

	install -d ${D}/usr/include/dnndk
	install -d ${D}/usr/include/vai
	install -m 0644 ${S}/include/dnndk/* ${D}/usr/include/dnndk
	install -m 0644 ${S}/include/vai/* ${D}/usr/include/vai

	install -d ${D}/usr/lib
	install -m 0655 ${S}/lib/* ${D}/usr/lib

	export TMPDIR="${WORKDIR}"
	install -d ${D}/${PYTHON_SITEPACKAGES_DIR}
	${STAGING_BINDIR_NATIVE}/pip3 install --disable-pip-version-check -v \
		 -t ${D}/${PYTHON_SITEPACKAGES_DIR} --no-cache-dir --no-deps \
		 	${WORKDIR}/python/Edge_Vitis_AI-1.0-py2.py3-none-any.whl
}

DEPENDS += " \
	python3 \
	python3-pip-native \
	python3-wheel-native \
	"
RDEPENDS_${PN} +=  "xrt"
RDEPENDS_${PN} += "${PN}-dev"

FILES_${PN} = "/usr/"

INSANE_SKIP_${PN} += "ldflags dev-deps"
INSANE_SKIP_${PN}-dev += "ldflags dev-elf"
