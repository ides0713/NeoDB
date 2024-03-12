set(IBINARY_DIRPATH ${PROJECT_BINARY_DIR})
set(ISOURCE_DIRPATH ${PROJECT_SOURCE_DIR})
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/src/server/global.h.in ${PROJECT_INCLUDE_DIR}/server/global.h)

# target_link_libraries(parser execution pthread)

add_executable(NeoDB_Server server_main.cpp server_def.cpp)

# target_include_directories(NeoDB_Server PRIVATE ${PROJECT_INCLUDE_DIR}/server)

add_subdirectory(common)
add_subdirectory(execution)
add_subdirectory(parse)
add_subdirectory(resolve)

target_link_libraries(NeoDB_Server neo0common neo0exec neo0parse neo0resolve jsoncpp)