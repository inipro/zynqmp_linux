FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = "file://ultra96-power-button-check.c;beginline=1;endline=25;md5=7616176d4afe94ff898b9dcae0fe5f9c"

SRC_URI = " \
    file://Makefile \
    file://ultra96-power-button.sh \
    file://ultra96-power-button-check.c \
    "

do_install() {
    install -d ${D}/sbin
    install -d ${D}${sysconfdir}/init.d/
    install -m 0755 ultra96-power-button-check ${D}/sbin
    install -m 0755 ${S}/ultra96-power-button.sh ${D}${sysconfdir}/init.d/ultra96-power-button.sh
}

