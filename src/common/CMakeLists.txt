add_subdirectory(type_traits)

add_library(fw-common STATIC
    details/logger.cpp
    details/shell.cpp
)
