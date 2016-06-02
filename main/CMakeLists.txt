set(Main_SRCS
    main.cpp
)

add_executable(anagram_finder
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(anagram_finder
    AnagramFinder
)

install(TARGETS anagram_finder DESTINATION bin)
