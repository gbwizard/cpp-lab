add_subdirectory(details)

add_executable(markov_compiler
    markov_compiler.cpp
)

target_link_libraries(markov_compiler
    markov-chain
    fw-common
    ${LIBS_LOGGING}
    ${LIBS_THREADING}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
)

add_executable(markov_generator
    markov_generator.cpp
)

target_link_libraries(markov_generator
    markov-chain
    fw-common
    ${LIBS_LOGGING}
    ${LIBS_THREADING}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
)
