cmake_minimum_required(VERSION 2.8)
project(log++)

set(CMAKE_BUILD_DIRECTORY Build/)
set(LIBRARY_OUTPUT_PATH Build/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O2")
endif()


find_package(Boost 1.49 COMPONENTS filesystem regex system REQUIRED)

include_directories(
	${Boost_INCLUDE_DIR}
	src
)

LINK_DIRECTORIES(
    ${Boost_LIBRARY_DIRS}
)

FILE(GLOB sources 
	src/log++/*.cpp
	src/log++/buffer/*.cpp
	src/log++/prefix/*.cpp
	src/log++/stream/*.cpp
)
FILE(GLOB headers 
	src/log++/*.h
	src/log++/buffer/*.h
	src/log++/prefix/*.h
	src/log++/stream/*.h
)

add_library(${PROJECT_NAME} SHARED ${sources})
target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES} 
)

######################
#Extract log++ version
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/src/log++/version.h" LIBLOGPP_HEADER_CONTENTS REGEX "#define LOGPP_VERSION_[A-Z]+ [0-9]+")
string(REGEX REPLACE ".*#define LOGPP_VERSION_MAJOR ([0-9]+).*" "\\1" LIBLOGPP_VERSION_MAJOR "${LIBLOGPP_HEADER_CONTENTS}")
string(REGEX REPLACE ".*#define LOGPP_VERSION_MINOR ([0-9]+).*" "\\1" LIBLOGPP_VERSION_MINOR "${LIBLOGPP_HEADER_CONTENTS}")
string(REGEX REPLACE ".*#define LOGPP_VERSION_PATCH ([0-9]+).*" "\\1" LIBLOGPP_VERSION_PATCH "${LIBLOGPP_HEADER_CONTENTS}")
  
set(LIBLOGPP_VERSION_STRING "${LIBLOGPP_VERSION_MAJOR}.${LIBLOGPP_VERSION_MINOR}.${LIBLOGPP_VERSION_PATCH}")
unset(LIBLOGPP_HEADER_CONTENTS)
######################


SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sebastien BESOMBES")
SET(CPACK_PACKAGE_VERSION "${LIBLOGPP_VERSION_STRING}")
SET(CPACK_PACKAGE_FILE_NAME  "lib${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}")
INCLUDE(CPack)

macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    foreach(HEADER ${${HEADER_LIST}})
        string(REGEX REPLACE ".*/src/" "" RELATIVEDIR ${HEADER})
        string(REGEX MATCH "(.*)[/\\]" DIR ${RELATIVEDIR})
        install(FILES ${HEADER} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${DIR})
    endforeach()
endmacro()

install (TARGETS ${PROJECT_NAME} 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
INSTALL_HEADERS_WITH_DIRECTORY(headers)

install (PROGRAMS Findlog++.cmake 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/log++
  RENAME log++Config.cmake)

include(CTest) 
add_subdirectory(tests/ut)


