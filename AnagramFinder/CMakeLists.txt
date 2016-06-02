set(AnagramFinder_SRCS
    config.h
    AnagramFinder.h
    AnagramFinder.cpp
    utilities.h
    utilities.cpp
)

# Declare the library
add_library(AnagramFinder STATIC
    ${AnagramFinder_SRCS}
)


# Specify here the include directories exported
# by this library
target_include_directories(AnagramFinder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
