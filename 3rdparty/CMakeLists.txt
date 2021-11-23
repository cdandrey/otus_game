cmake_minimum_required(VERSION 3.2)

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")

add_compile_options(${CMAKE_CXX_FLAGS})

# expected
add_subdirectory("expected")

set(OTG_3RDPARTY_INCLUDE_DIRECTORIES "${INCLUDE_DIRS}" PARENT_SCOPE)