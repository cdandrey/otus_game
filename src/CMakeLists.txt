cmake_minimum_required(VERSION 3.2)

set(adapters_headers
    adapters/AbstractAdapter.h
    adapters/AbstractCommand.h
    adapters/AdapterMovable.h
    adapters/AdapterRotable.h
)

set(adapters_sources
    adapters/AbstractAdapter.cpp
    adapters/AdapterMovable.cpp
    adapters/AdapterRotable.cpp
)

set(commands_headers
    commands/AbstractCommand.h
    commands/CommandMovable.h
    commands/CommandRotable.h
    commands/CommandWorker.h
    commands/CommandStop.h
    commands/CommandInterrupt.h
)

set(commands_sources
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