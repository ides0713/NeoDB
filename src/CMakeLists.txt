include_directories(${CMAKE_CURRENT_SOURCE_DIR})


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(client)
add_subdirectory(server)

# add_executable(rmdb rmdb.cpp)
# target_link_libraries(rmdb parser execution readline pthread planner analyze)