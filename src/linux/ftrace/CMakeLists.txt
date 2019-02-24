set(TARGET ftracer)

add_executable(${TARGET}
    ftracer.cpp
)

target_link_libraries(${TARGET}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
