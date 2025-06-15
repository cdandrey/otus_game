cmake_minimum_required(VERSION 3.15)

set(this tb_main)
set(source tb_main.cpp)

add_executable(${this} ${source})
if (WIN32)
    # Convert Windows paths to CMake-style paths (slashes)
    file(TO_CMAKE_PATH "$ENV{GTEST_DEBUG_DIR}" GTEST_DEBUG_DIR_FIXED)
    file(TO_CMAKE_PATH "$ENV{GTEST_DIR}" GTEST_DIR_FIXED)

    set(GTEST_INCLUDE_DEBUG "${GTEST_DEBUG_DIR_FIXED}/include")
    set(GTEST_INCLUDE_RELEASE "${GTEST_DIR_FIXED}/include")

    target_include_directories(tb_main PRIVATE
        $<$<CONFIG:Debug>:${GTEST_INCLUDE_DEBUG}>
        $<$<CONFIG:Release>:${GTEST_INCLUDE_RELEASE}>
    )

    set(GTEST_LIB_DEBUG "${GTEST_DEBUG_DIR_FIXED}/lib/gtest.lib")
    set(GTEST_MAIN_LIB_DEBUG "${GTEST_DEBUG_DIR_FIXED}/lib/gtest_main.lib")
    set(GTEST_LIB_RELEASE "${GTEST_DIR_FIXED}/lib/gtest.lib")
    set(GTEST_MAIN_LIB_RELEASE "${GTEST_DIR_FIXED}/lib/gtest_main.lib")

    # Link GTest for the correct build type
    target_link_libraries(tb_main
        PRIVATE
            OtgLib
            $<$<CONFIG:Debug>:${GTEST_LIB_DEBUG}>
            $<$<CONFIG:Debug>:${GTEST_MAIN_LIB_DEBUG}>
            $<$<CONFIG:Release>:${GTEST_LIB_RELEASE}>
            $<$<CONFIG:Release>:${GTEST_MAIN_LIB_RELEASE}>
            ${CMAKE_THREAD_LIBS_INIT}
    )
else()
    find_package(GTest REQUIRED)
    target_link_libraries(${this} GTest::gtest GTest::gtest_main pthread)
endif()

# Compiler warnings
if (MSVC)
    target_compile_options(
        ${this}
        PRIVATE
        /W4
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Release>:/MD>
    )
else ()
    target_compile_options(
        ${this}
        PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

# Register as test
add_test(${this} ${this})


