cmake_minimum_required( VERSION 3.20 )

# set the project name
project(ANT-SDK VERSION 3.9.0 DESCRIPTION "ANT wireless communications library")

option(BUILD_SHARED_LIBS "Build as a shared library." true)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the library
add_Library(ant src/libant.cpp)

set_target_properties(ant PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 3
	PUBLIC_HEADER src/libant.h)

target_include_directories(ant PRIVATE
	src
	src/ANTFS
	src/common
	src/dsi
	src/inc
	src/serial
	src/serial/device_management
	src/system
	src/USB
	src/USB/device_handles
	src/USB/devices
)

target_sources(ant PRIVATE
	src/ANTFS/antfs_client_channel.cpp
	src/ANTFS/antfs_directory.c
	src/ANTFS/antfs_host.cpp
	src/ANTFS/antfs_host_channel.cpp
	src/common/checksum.c
	src/common/crc.c
	src/serial/device_management/dsi_ant_device.cpp
	src/serial/device_management/dsi_ant_device_polling.cpp
	src/system/dsi_convert.c
	src/system/dsi_debug.cpp
	src/serial/dsi_framer.cpp
	src/serial/dsi_framer_ant.cpp
	src/serial/dsi_framer_integrated_antfs_client.cpp
	src/serial/dsi_serial.cpp
	src/serial/dsi_serial_generic.cpp
	src/system/dsi_thread_posix.c
	src/system/dsi_timer.cpp
	src/system/macros.c
	src/USB/devices/usb_device.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	find_library(IOKIT NAMES IOKit REQUIRED)
	find_library(COCOA NAMES Cocoa REQUIRED)

	target_link_libraries(ant ${IOKIT} ${COCOA})

	target_include_directories(ant PRIVATE
		src/USB/iokit_driver
	)
	target_sources(ant PRIVATE
		src/dsi/dsi_libusb_library_mac.cpp
		src/serial/dsi_vcp_si.cpp
		src/USB/devices/usb_device_vcp.cpp
		src/USB/device_handles/usb_device_handle_vcp.cpp
		src/USB/device_handles/usb_device_handle_mac.cpp
		src/serial/dsi_serial_iokit.cpp
		src/USB/iokit_driver/iokit_device.cpp
		src/USB/iokit_driver/iokit_device_handle.cpp
		src/USB/iokit_driver/iokit_device_list.cpp
		src/USB/iokit_driver/iokit_interface.cpp
		src/USB/iokit_driver/iokit_transfer.cpp
		src/USB/devices/usb_device_iokit.cpp
		src/USB/device_handles/usb_device_handle_si_iokit.cpp
		src/USB/device_handles/usb_device_handle_iokit.cpp
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME EQUAL "FreeBSD")
	find_library(LIBUSB usb REQUIRED)

	target_link_libraries(ant ${LIBUSB})
	target_compile_definitions(ant PUBLIC LIBUSB_DRIVER)

	target_sources(ant PRIVATE
		src/dsi/dsi_libusb_library_linux.cpp
		src/serial/dsi_serial_libusb_linux.cpp
		src/USB/device_handles/usb_device_handle_libusb_linux.cpp
		src/USB/device_handles/usb_device_handle_linux.cpp
		src/USB/devices/usb_device_libusb_linux.cpp
	)
else()
	message( FATAL_ERROR "No rules for system `${CMAKE_SYSTEM_NAME}`" )
endif()


include(GNUInstallDirs)
install(TARGETS ant
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

