cmake_minimum_required(VERSION 3.2)

set(adapters_headers
    adapters/AbstractAdapter.h
    adapters/AbstractAdapterPropertys.h
    adapters/AdapterBurnFuel.h
    adapters/AdapterCheckFuel.h
    adapters/AdapterMovable.h
    adapters/AdapterRotable.h
)

set(adapters_sources
    adapters/AbstractAdapter.cpp
    adapters/AdapterBurnFuel.cpp
    adapters/AdapterCheckFuel.cpp
    adapters/AdapterMovable.cpp
    adapters/AdapterRotable.cpp
)

set(commands_headers
    commands/AbstractCommand.h
    commands/CommandCheckFuel.h
    commands/CommandInterrupt.h
    commands/CommandMovable.h
    commands/CommandRotable.h
    commands/CommandStop.h
    commands/CommandWorker.h
)

set(commands_sources
    commands/CommandCheckFuel.cpp
    commands/CommandInterrupt.cpp
    commands/CommandMovable.cpp
    commands/CommandRotable.cpp
    commands/CommandStop.cpp
    commands/CommandWorker.cpp
)

set(object_headers
    objects/Objects.h
)

set(object_sources
    objects/Objects.cpp
)

set(types_headers
    types/Angel.h
    types/ExceptionError.h
    types/Point.h
    types/Property.h
    types/Property_internal.h
    types/VelocityRotate.h
    types/VectorVelocity.h
)

set(types_sources
    types/Angel.cpp
    types/ExceptionError.cpp
    types/Point.cpp
    types/VelocityRotate.cpp
    types/VectorVelocity.cpp
)

add_library(OtgLib
    STATIC
    ${adapters_headers}
    ${adapters_sources}
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