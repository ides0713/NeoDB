cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(NeoDB)

MESSAGE(STATUS "This is Project source dir " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "This is PROJECT_BINARY_DIR dir " ${PROJECT_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include_directories(deps/jsoncpp/include)

# file(GLOB_RECURSE JSONCPP_SOURCE deps/jsoncpp/src/lib_json/*.cpp)
# file(GLOB_RECURSE JSONCPP_HEADER deps/jsoncpp/inlcude/*.h)
# add_library(jsoncpp ${JSONCPP_HEADER} ${JSONCPP_SOURCE})

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(src)