add_subdirectory(client_events)
add_subdirectory(computer_club)
add_subdirectory(parse)
add_subdirectory(validate)

add_library(main OBJECT main.cpp)

list(APPEND GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS
    -DNDEBUG
    -O2
)

list(APPEND GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS
    -g
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    message(STATUS "RELEASE BUILD TYPE")
    foreach(target IN ZIP_LISTS MANAGE_COMPUTER_CLUB_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS "DEBUG BUILD TYPE")
    foreach(target IN ZIP_LISTS MANAGE_COMPUTER_CLUB_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
endif()
