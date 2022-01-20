cmake_minimum_required(VERSION 3.2)

set(commands_headers
    commands/AbstractAdapter.h
    commands/AbstractCommand.h
    commands/AdapterMovable.h
    commands/AdapterRotable.h
    commands/CommandMovable.h
    commands/CommandRotable.h
    commands/CommandWorker.h
    commands/CommandStop.h
    commands/CommandInterrupt.h
)

set(commands_sources
    commands/AbstractAdapter.cpp
    commands/AdapterMovable.cpp
    commands/AdapterRotable.cpp
    commands/CommandMovable.cpp
    commands/CommandRotable.cpp
    commands/CommandWorker.cpp
    commands/CommandStop.cpp
    commands/CommandInterrupt.cpp
)

set(object_headers
    objects/Objects.h
)

set(object_sources
    objects/Objects.cpp
)

set(types_headers
    types/Property.h
    types/Property_internal.h
    types/ExceptionError.h
    types/Point.h
    types/VectorVelocity.h
)

set(types_sources
    types/ExceptionError.cpp
    types/Point.cpp
    types/VectorVelocity.cpp
)

add_library(OtgLib
    STATIC
    ${commands_headers}
    ${commands_sources}
    ${object_headers}
    ${object_sources}
    ${types_headers}
    ${types_sources}
)

target_compile_definitions(OtgLib
    PUBLIC
    UNICODE
    _UNICODE
)