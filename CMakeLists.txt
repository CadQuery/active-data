cmake_minimum_required (VERSION 3.0.0 FATAL_ERROR)

# Project name
project (ActiveData CXX)

# Install dir of the built project
set (INSTALL_DIR "" CACHE PATH "Where to install" )
set (CMAKE_INSTALL_PREFIX "${INSTALL_DIR}" CACHE INTERNAL "" FORCE )

# Build configurations
set (CMAKE_CONFIGURATION_TYPES Release Debug RelWithDebInfo CACHE INTERNAL "" FORCE)

#-------------------------------------------------------------------------------
# Find 3rd-parties
#-------------------------------------------------------------------------------

include (${CMAKE_SOURCE_DIR}/cmake/actdata_3rdparty_macros.cmake)

ACTDATA_RETRIEVE_VERSION(${CMAKE_SOURCE_DIR}/src/ActiveDataAPI/ActAPI_Version.h VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

message (STATUS "Active Data VERSION_MAJOR: ${VERSION_MAJOR}")
message (STATUS "Active Data VERSION_MINOR: ${VERSION_MINOR}")
message (STATUS "Active Data VERSION_PATCH: ${VERSION_PATCH}")

# Set a directory containing all 3-rd parties
set (3RDPARTY_DIR "" CACHE PATH "The root directory for all 3-rd parties")

# Set use tbb optional flag
set (USE_TBB OFF CACHE BOOL "TBB is optional 3-rd party. Building with TBB enables multi-threaded Active Data tools (i.e. detached execution of Tree Functions).")
if (USE_TBB)
  add_definitions (-DUSE_TBB)
endif()

if (NOT DEFINED ${3RDPARTY_DIR} AND ${3RDPARTY_DIR} STREQUAL "")
    message (FATAL_ERROR "... root 3rdparty directory was not found")
endif()

# OCCT
include (${CMAKE_SOURCE_DIR}/cmake/actdata_OCCT.cmake)

# OCCT 3rdparty
include (${CMAKE_SOURCE_DIR}/cmake/actdata_OCCT_3rdparty.cmake)

if (USE_TBB)
  set (3RDPARTY_DLL_PATH "${3RDPARTY_DLL_PATH};${3RDPARTY_tbb_DLL_DIR}")
endif()

set (3RDPARTY_DLL_DEB_PATH "${3RDPARTY_DLL_PATH}")

if (3RDPARTY_OCCT_DLL_DIR_DEBUG AND EXISTS "${3RDPARTY_OCCT_DLL_DIR_DEBUG}")
  set (3RDPARTY_DLL_DEB_PATH "${3RDPARTY_DLL_DEB_PATH};${3RDPARTY_OCCT_DLL_DIR_DEBUG}")
endif()

set (3RDPARTY_DLL_PATH "${3RDPARTY_DLL_PATH};${3RDPARTY_OCCT_DLL_DIR};")

#-------------------------------------------------------------------------------
string (REGEX REPLACE ";" " " 3RDPARTY_NOT_INCLUDED "${3RDPARTY_NOT_INCLUDED}")

# check all 3rdparty paths
if (3RDPARTY_NOT_INCLUDED)
  message (FATAL_ERROR "NOT FOUND: ${3RDPARTY_NOT_INCLUDED}")
endif()

#-------------------------------------------------------------------------------
# Executable
#-------------------------------------------------------------------------------

# Configure warnings level
if (MSVC)
  add_definitions (/W4)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHa")
elseif (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions (-Wall -pedantic)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
else()
  message ("Unknown compiler")
endif()

#-------------------------------------------------------------------------------
# Output
#-------------------------------------------------------------------------------

# build directories
set (OS_WITH_BIT "${PLATFORM}${COMPILER_BITNESS}")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/lib")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/libi")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/bini")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/libi")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/libd")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/bind")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/libd")

if (WIN32)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/bin")
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/bini")
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_BINARY_DIR}/${OS_WITH_BIT}/${COMPILER}/bind")
endif()

#-------------------------------------------------------------------------------
# Sub-projects
#-------------------------------------------------------------------------------

add_subdirectory(${CMAKE_SOURCE_DIR}/src/ActiveDataAPI)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/ActiveDataAux)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/ActiveData)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/ActiveDataTestLib)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/ActiveDataTest)

#-------------------------------------------------------------------------------
# Folders
#-------------------------------------------------------------------------------

################################################################################
set_property(TARGET ActiveData        PROPERTY FOLDER Core)
set_property(TARGET ActiveDataAPI     PROPERTY FOLDER Core)
set_property(TARGET ActiveDataAux     PROPERTY FOLDER Core)
################################################################################
set_property(TARGET ActiveDataTest    PROPERTY FOLDER Tests)
set_property(TARGET ActiveDataTestLib PROPERTY FOLDER Tests)
################################################################################

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

#-------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------

if (EXISTS "${3RDPARTY_DIR}/Redistributable/msvcp120.dll")
  install (FILES "${3RDPARTY_DIR}/Redistributable/msvcp120.dll" DESTINATION bin)
endif()

if (EXISTS "${3RDPARTY_DIR}/Redistributable/msvcr120.dll")
  install (FILES "${3RDPARTY_DIR}/Redistributable/msvcr120.dll" DESTINATION bin)
endif()
