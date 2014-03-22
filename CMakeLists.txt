cmake_minimum_required(VERSION 2.8)
project(log++)

set(CMAKE_BUILD_DIRECTORY Build/)
set(LIBRARY_OUTPUT_PATH Build/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O2")
endif()


find_package(Boost 1.53 COMPONENTS filesystem regex system REQUIRED)

include_directories(
	${Boost_INCLUDE_DIR}
	src
)

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

FILE(GLOB sources src/log++/*.cpp)
FILE(GLOB headers src/log++/*.h)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_library(${PROJECT_NAME} ${sources})
else ()
	add_library(${PROJECT_NAME} SHARED ${sources})
endif()
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sebastien BESOMBES")
SET(CPACK_PACKAGE_VERSION "1.1.0")
SET(CPACK_PACKAGE_FILE_NAME  "lib${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}")
INCLUDE(CPack)

#install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
#    COMPONENT runtime)
install (TARGETS ${PROJECT_NAME} 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/log++)

add_subdirectory(tests)

enable_testing()