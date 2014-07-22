# - Find LibLOGPP
# Find LibLOGPP headers and library
#
#  LIBLOGPP_FOUND             - True if liblog++ is found.
#  LIBLOGPP_INCLUDE_DIRS      - Directory where liblog++ headers are located.
#  LIBLOGPP_LIBRARIES         - log++ libraries to link against.
#  LIBLOGPP_VERSION_MAJOR     - The major version of log++
#  LIBLOGPP_VERSION_MINOR     - The minor version of log++
#  LIBLOGPP_VERSION_PATCH     - The patch version of log++
#  LIBLOGPP_VERSION_STRING    - version number as a string (ex: "2.0.0")

#=============================================================================
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
# MA 02110-1301, USA.
#=============================================================================

find_path(LIBLOGPP_INCLUDE_DIR log++/log++.h)
find_library(LIBLOGPP_LIBRARY log++)
find_library(LIBLOGPP_MONGOCLIENT mongoclient)
find_library(LIBLOGPP_PTHREAD pthread)
find_library(LIBLOGPP_CRYPTO crypto)
find_library(LIBLOGPP_SSL ssl)

if(LIBLOGPP_INCLUDE_DIR AND EXISTS "${LIBLOGPP_INCLUDE_DIR}/log++/version.h")
    file(STRINGS "${LIBLOGPP_INCLUDE_DIR}/log++/version.h" LIBLOGPP_HEADER_CONTENTS REGEX "#define LOGPP_VERSION_[A-Z]+ [0-9]+")

    string(REGEX REPLACE ".*#define LOGPP_VERSION_MAJOR ([0-9]+).*" "\\1" LIBLOGPP_VERSION_MAJOR "${LIBLOGPP_HEADER_CONTENTS}")
    string(REGEX REPLACE ".*#define LOGPP_VERSION_MINOR ([0-9]+).*" "\\1" LIBLOGPP_VERSION_MINOR "${LIBLOGPP_HEADER_CONTENTS}")
    string(REGEX REPLACE ".*#define LOGPP_VERSION_PATCH ([0-9]+).*" "\\1" LIBLOGPP_VERSION_PATCH "${LIBLOGPP_HEADER_CONTENTS}")

    set(LIBLOGPP_VERSION_STRING "${LIBLOGPP_VERSION_MAJOR}.${LIBLOGPP_VERSION_MINOR}.${LIBLOGPP_VERSION_PATCH}")
    unset(LIBLOGPP_HEADER_CONTENTS)
endif()

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibLOGPP  REQUIRED_VARS  LIBLOGPP_INCLUDE_DIR
                                                           LIBLOGPP_LIBRARY
                                            VERSION_VAR    LIBLOGPP_VERSION_STRING
                                 )

if (LIBLOGPP_FOUND)
    message("-- Found the log++ library")
    
    find_package(Boost 1.49 COMPONENTS filesystem regex system thread REQUIRED)

    set(LIBLOGPP_LIBRARIES 
        ${LIBLOGPP_MONGOCLIENT}
        ${LIBLOGPP_PTHREAD} 
        ${LIBLOGPP_CRYPTO} 
        ${LIBLOGPP_SSL}
        ${LIBLOGPP_LIBRARY}
        ${Boost_LIBRARIES}
    )
    set(LIBLOGPP_INCLUDE_DIRS ${LIBLOGPP_INCLUDE_DIR})
endif ()

mark_as_advanced( LIBLOGPP_INCLUDE_DIR LIBLOGPP_LIBRARY )
