cmake_minimum_required(VERSION 3.15)

set(OtgLib_sources
    adapters/AbstractAdapter.cpp
    adapters/AdapterBurnFuel.cpp
    adapters/AdapterCheckFuel.cpp
    adapters/AdapterMovable.cpp
    adapters/AdapterRotable.cpp

    commands/CommandCheckFuel.cpp
    commands/CommandInterrupt.cpp
    commands/CommandMovable.cpp
    commands/CommandRotable.cpp
    commands/CommandStop.cpp
    commands/CommandWorker.cpp

    objects/Objects.cpp

    types/Angel.cpp
    types/ExceptionError.cpp
    types/Point.cpp
    types/VelocityRotate.cpp
    types/VectorVelocity.cpp
)

add_library(OtgLib STATIC ${OtgLib_sources})

# Add includes — directories only, NOT files!
target_include_directories(OtgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link to third-party INTERFACE library Expected (header-only)
target_link_libraries(OtgLib PUBLIC Expected)

# Set Unicode macros for all files in this target
target_compile_definitions(OtgLib PUBLIC UNICODE _UNICODE)

# Add extra compiler warnings depending on the compiler
if(MSVC)
    target_compile_options(OtgLib PRIVATE /W4)
else()
    target_compile_options(OtgLib PRIVATE -Wall -Wextra -pedantic)
endif()
