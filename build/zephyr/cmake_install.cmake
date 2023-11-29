# Install script for directory: /home/ark/ncs/v2.1.2/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/ark/ncs/toolchains/v2.1.2/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/soc/arm/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/liblc3codec/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/tinycbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/TraceRecorder/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/ark/ncs/v2.1.2/zephyr/samples/drivers/audio/dmic/build/zephyr/cmake/reports/cmake_install.cmake")
endif()

