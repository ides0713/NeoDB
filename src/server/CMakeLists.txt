include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# add_subdirectory(common)
# add_subdirectory(execution)
add_subdirectory(parse)
# add_subdirectory(resolve)

# target_link_libraries(parser execution pthread)

add_executable(NeoDB_Server server.cpp)
target_link_libraries(NeoDB_Server parse)