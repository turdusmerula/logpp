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
    ${CMAKE_CURRENT_SOURCE_DIR}/../cots/mongo-cxx-driver/build/install/include
)

LINK_DIRECTORIES(
    ${Boost_LIBRARY_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../cots/mongo-cxx-driver/build/install/lib
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

include(CTest) 
add_subdirectory(tests/ut)


