cmake_minimum_required(VERSION 3.15)

set (this OtusTankGame)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${this} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${this} VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(3rdparty)
add_subdirectory(src)

add_executable(OTG src/main.cpp)

target_link_libraries(OTG PRIVATE OtgLib Expected)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER} AND NOT "$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_CONTACT cdandrey@gmail.com)

    include(CPack)

endif()

enable_testing()
add_subdirectory("test")
