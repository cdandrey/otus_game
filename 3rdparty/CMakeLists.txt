cmake_minimum_required(VERSION 3.15)

# Header-only libraries do not require compilation; simply mark them as INTERFACE
add_subdirectory(expected)

# Collect all header file directories from nested folders.
set(OTG_3RDPARTY_INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/expected"
    # If you have more, add them here.
    # "${CMAKE_CURRENT_SOURCE_DIR}/что-то-ещё"
    PARENT_SCOPE
)