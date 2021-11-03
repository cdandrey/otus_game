
#pragma once

namespace otg {

enum class PropertyKey;

template<PropertyKey key>
struct Property {};

#define SPECIFY_PROPERTY_TYPE(Key,Type)                               \
    template<>                                                        \
    struct Property<PropertyKey::Key>                                 \
    {                                                                 \
        using type = Type;                                            \
        static constexpr PropertyKey key = PropertyKey::Key;          \
        static constexpr auto init_value = std::pair{key,type{}};     \
    };                                                                \
    using Key##Property = Property<PropertyKey::Key>;                 \

}