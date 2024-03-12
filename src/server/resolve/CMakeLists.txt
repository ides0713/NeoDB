file(GLOB RESOLVE_SOURCE *.cpp)
add_library(neo0resolve SHARED ${RESOLVE_SOURCE})
target_include_directories(neo0resolve PUBLIC ${PROJECT_INCLUDE_DIR}/server)