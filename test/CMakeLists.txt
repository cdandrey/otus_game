cmake_minimum_required(VERSION 3.2)

if (MSVC)
    if (${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} STREQUAL "x64")
        set(GTEST_ROOT $ENV{GTEST_LIBRARY_DIR})
    else()
        set(GTEST_ROOT $ENV{GTEST_LIBRARY86_DIR})
    endif()
    set(GTEST_INCLUDE_DIR $ENV{GTEST_INCLUDE_DIR})
endif()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(this tb_main)
set(source tb_main.cpp)

add_executable(${this} ${source})

target_include_directories(
    ${this}
    PRIVATE
    ${GTEST_INCLUDE_DIR}
)

target_link_libraries(${this} ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${this} ${CMAKE_THREAD_LIBS_INIT})

if (MSVC)
    target_compile_options(
        ${this}
        PRIVATE
        /W4
        $<$<CONFIG:Debug>:/MT>
        $<$<CONFIG:Release>:/MT>

    )
else ()
    target_compile_options(
        ${this}
        PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(${this} ${this})


