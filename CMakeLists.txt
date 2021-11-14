cmake_minimum_required(VERSION 3.2)

set (this OtusTankGame)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${this} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${this} VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(OTG
    src/main.cpp
)
target_link_libraries(OTG
    OtgLib
)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    
    set(CPACK_GENERATOR DEB)

    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    set(CPACK_PACKAGE_CONTACT cdandrey@gmail.com)

    include(CPack)

endif()

add_subdirectory(test)
enable_testing()