file(GLOB EXEC_SOURCE *.cpp)
add_library(neo0exec SHARED ${EXEC_SOURCE})
target_include_directories(neo0exec PUBLIC ${PROJECT_INCLUDE_DIR}/server)