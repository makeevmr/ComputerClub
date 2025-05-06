cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(computer_club LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_DEBUG "")

list(APPEND MANAGE_COMPUTER_CLUB_TARGETS
    validate
    computer_club
    client_events
    parse
    main
)

# list(APPEND TAPE_TESTS_TARGETS
#     tape
#     delay_parse
#     convert_file
#     sort_tape
#     test_int_tape
# )

add_subdirectory(src)

# manage_computer_club
add_executable(manage_computer_club)
target_link_libraries(manage_computer_club
    PRIVATE
    ${MANAGE_COMPUTER_CLUB_TARGETS}
)

# tape_tests
# enable_testing()
#
# find_package(GTest REQUIRED)
#
# add_executable(tape_tests)
# target_link_libraries(tape_tests PRIVATE
#     GTest::GTest
#     ${TAPE_TESTS_TARGETS}
# )
#
# add_test(tape_gtests tape_tests)
