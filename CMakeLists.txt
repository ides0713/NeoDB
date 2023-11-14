cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(NeoDB)

MESSAGE(STATUS "This is Project source dir " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "This is PROJECT_BINARY_DIR dir " ${PROJECT_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(deps/jsoncpp/include)

file(GLOB JSONCPP_SOURCE deps/jsoncpp/src/lib_json/*.cpp)
add_library(jsoncpp STATIC ${JSONCPP_SOURCE})

ADD_SUBDIRECTORY(src)