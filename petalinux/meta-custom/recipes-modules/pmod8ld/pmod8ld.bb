LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

inherit module

SRC_URI = "file://Makefile \
           file://pmod8ld.c \
          "

S = "${WORKDIR}"

KERNEL_MODULE_AUTOLOAD += "pmod8ld"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

