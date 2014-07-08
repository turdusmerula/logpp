cmake_minimum_required(VERSION 2.8)
project(log++-unit-test)

set(CMAKE_BUILD_DIRECTORY Build/)
set(EXECUTABLE_OUTPUT_PATH Build/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -O2")

find_package(Boost 1.49 COMPONENTS filesystem regex system thread REQUIRED)

include_directories(
	src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../cots/mongo-cxx-driver/build/install/include
)

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../cots/mongo-cxx-driver/build/install/lib
)

FILE(GLOB sources src/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} 
    cppunit 
    log++  
    ${Boost_LIBRARIES} 
    pthread 
    crypto 
    ssl 
    mongoclient
)

