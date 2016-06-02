file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testAnagramfinder ${SRCS})

TARGET_LINK_LIBRARIES(testAnagramfinder
    AnagramFinder
    libgtest
)

add_test(NAME testAnagramFinder
         COMMAND testAnagramFinder)
