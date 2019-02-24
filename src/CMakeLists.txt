include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(common)
add_subdirectory(algo)
add_subdirectory(tasks)
add_subdirectory(linux)
