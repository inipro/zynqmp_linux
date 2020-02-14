LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://autostart.sh"

S = "${WORKDIR}"

inherit update-rc.d

INITSCRIPT_NAME = "autostart"
INITSCRIPT_PARAMS = "start 99 5 ."

do_install() {
	    install -d ${D}${sysconfdir}/init.d
		    install -m 0755 ${S}/autostart.sh ${D}${sysconfdir}/init.d/autostart
}


RDEPENDS_${PN}_append += "bash"


