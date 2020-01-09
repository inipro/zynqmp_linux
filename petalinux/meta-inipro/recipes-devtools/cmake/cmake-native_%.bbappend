FILESEXTRAPATHS_prepend := "${THISDIR}/cmake:"

SRC_URI += "file://FindXRT.cmake \
			file://FindGLIB.cmake \
			file://FindGStreamer.cmake \
			file://FindLibDRM.cmake \
"

do_install_append() {
	mkdir -p ${D}${datadir}/cmake-${CMAKE_MAJOR_VERSION}/Modules
	install -m 644 ${WORKDIR}/FindXRT.cmake ${D}${datadir}/cmake-${CMAKE_MAJOR_VERSION}/Modules/
	install -m 644 ${WORKDIR}/FindGLIB.cmake ${D}${datadir}/cmake-${CMAKE_MAJOR_VERSION}/Modules/
	install -m 644 ${WORKDIR}/FindGStreamer.cmake ${D}${datadir}/cmake-${CMAKE_MAJOR_VERSION}/Modules/
	install -m 644 ${WORKDIR}/FindLibDRM.cmake ${D}${datadir}/cmake-${CMAKE_MAJOR_VERSION}/Modules/
}
