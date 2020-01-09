#
# FindXRT
# ----------
# Finds the Xilinx Runtime (XRT) library
#
# This will define the following variables:
#
# XRT_FOUND - system has XRT
# XRT_INCLUDE_DIRS - the XRT include directory
# XRT_LIBRARIES - the XRT libraries
# XCL_INCLUDE_DIRS - the XCL include directory
# XCL_LIBRARIES - the XCL libraries
#

set (XRT_INC_DIR_SUFFIX "xrt")

# XRT - Xilinx Runtime
find_path (XRT_INCLUDE_DIRS NAMES xclbin.h
                            PATH_SUFFIXES ${XRT_INC_DIR_SUFFIX})
find_library(XRT_LIBRARIES NAMES xrt_core)

# XCL - Xilinx OpenCL Extensions
find_path (XCL_INCLUDE_DIRS NAMES CL/cl_ext_xilinx.h
                            PATH_SUFFIXES ${XRT_INC_DIR_SUFFIX})
find_library(XCL_LIBRARIES NAMES xilinxopencl)

set (_XRT_REQUIRED_VARS XCL_LIBRARIES XRT_LIBRARIES XCL_INCLUDE_DIRS XRT_INCLUDE_DIRS)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(XRT REQUIRED_VARS ${_XRT_REQUIRED_VARS})

mark_as_advanced(XCL_INCLUDE_DIRS XRT_INCLUDE_DIRS XCL_LIBRARIES XRT_LIBRARIES)
