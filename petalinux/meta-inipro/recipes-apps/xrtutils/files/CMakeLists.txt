cmake_minimum_required (VERSION 3.12)

project(xrtutils VERSION 1.0.0)

include(GNUInstallDirs)

find_package(OpenCL REQUIRED)
find_package(XRT REQUIRED)

add_library (xrtutils SHARED)

target_sources(xrtutils
	PRIVATE
		xcl2.cpp
		xrtutils.cpp
)

add_library(xrtutils::xrtutils ALIAS xrtutils)

target_include_directories (xrtutils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
  ${OpenCL_INCLUDE_DIRS}
  ${XRT_INCLUDE_DIRS}
)

set_target_properties(xrtutils
	PROPERTIES
	SOVERSION 1
)

target_link_libraries (xrtutils PRIVATE
  ${OpenCL_LIBRARIES}
)

install(TARGETS xrtutils EXPORT xrtutilsTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES xcl2.hpp xrt_mapping_buffer.h xrtutils.hpp 
	DESTINATION  ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT xrtutilsTargets
	FILE xrtutilsTargets.cmake
	NAMESPACE xrtutils::
	DESTINATION "${CMAKE_INSTALL_DATADIR}/xrtutils/cmake"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/xrtutilsConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
	"${CMAKE_CURRENT_LIST_DIR}/xrtutilsConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/xrtutilsConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/xrtutils/cmake"
)

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/xrtutilsConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/xrtutilsConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_DATADIR}/xrtutils/cmake"
)

