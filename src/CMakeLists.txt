include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(client)
add_subdirectory(server)

# add_executable(rmdb rmdb.cpp)
# target_link_libraries(rmdb parser execution readline pthread planner analyze)