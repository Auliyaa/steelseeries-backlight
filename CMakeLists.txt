#--------------------------------------
# Global compilation directives
#--------------------------------------
cmake_minimum_required(VERSION 3.1)

#----------------------------------------------------------------------------
# Project options
#----------------------------------------------------------------------------
# Overload option() to display currently selected options and automatically add compiler definitions
# Add a debug dump to the option() function
function(option name)
  _option(${name} ${ARGN})
  message("-- ${name} is set to ${${name}}")
  if(${name})
    add_definitions(-D${name})
  endif(${name})
endfunction(option)

#----------------------------------------------------------------------------
# Compiler flags
#----------------------------------------------------------------------------
# GCC specific flags
if(CMAKE_COMPILER_IS_GNUCXX)
  # Enable C++11
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

  # Enable all warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

  # Treat all warnings as errors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

  # Disable "statement has no effect" warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-value")
endif(CMAKE_COMPILER_IS_GNUCXX)

#----------------------------------------------------------------------------
# External libraries
#----------------------------------------------------------------------------
# TClap
find_path(TCLAP_INCLUDE_DIR tclap/CmdLine.h)

# hidapi
find_path(HIDAPI_INCLUDE_DIR hidapi/hidapi.h)
find_library(HIDAPI_LIBRARY hidapi-libusb)

#----------------------------------------------------------------------------
# Overriding functions & setting up global macros
#----------------------------------------------------------------------------
# add_library
function(ADD_LIBRARY name)
  _add_library(${name} ${ARGN})

  # CMake >= 3.1.0 does not allow to set the INSTALL_RPATH property on INTERFACE_LIBRARY target type
  get_target_property(TARGET_TYPE ${name} TYPE)
  if(NOT "${TARGET_TYPE}" STREQUAL "INTERFACE_LIBRARY")
    set_target_properties(${name} PROPERTIES INSTALL_RPATH "$ORIGIN")
  endif(NOT "${TARGET_TYPE}" STREQUAL "INTERFACE_LIBRARY")
endfunction(ADD_LIBRARY)

# add_executable
function(ADD_EXECUTABLE name)
  _add_executable(${name} ${ARGN})
  set_target_properties(${name} PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
endfunction(ADD_EXECUTABLE)

#----------------------------------------------------------------------------
# Installation directories
#----------------------------------------------------------------------------
set(BINARY_INSTALL_DIR  bin)
set(LIBRARY_INSTALL_DIR lib)
set(INCLUDE_INSTALL_DIR include)
set(SHARED_INSTALL_DIR share)

#--------------------------------------
# Main target
#--------------------------------------
include_directories(
  ${TCLAP_INCLUDE_DIR}
  ${HIDAPI_INCLUDE_DIR}
)

add_executable(kbd-light
  main.cpp
  msi_keyboard.cpp
)

target_link_libraries(kbd-light
  ${HIDAPI_LIBRARY}
)

install(TARGETS kbd-light
  RUNTIME DESTINATION ${BINARY_INSTALL_DIR}
  LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
)
