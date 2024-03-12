file(GLOB COMMON_SOURCE *.cpp)
add_library(neo0common SHARED ${COMMON_SOURCE})
target_include_directories(neo0common PUBLIC ${PROJECT_INCLUDE_DIR}/server)