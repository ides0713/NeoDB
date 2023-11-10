include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(IBINARY_DIRPATH ${PROJECT_BINARY_DIR})
set(ISOURCE_DIRPATH ${PROJECT_SOURCE_DIR})
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/src/server/global.h.in ${PROJECT_SOURCE_DIR}/src/server/global.h)

add_subdirectory(common)
# add_subdirectory(execution)
add_subdirectory(parse)
# add_subdirectory(resolve)

# target_link_libraries(parser execution pthread)

add_executable(NeoDB_Server server_main.cpp)
target_link_libraries(NeoDB_Server parse common)