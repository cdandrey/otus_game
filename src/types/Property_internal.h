
#pragma once

namespace otg {

using PropertyKey = std::string_view;

template<const PropertyKey &key>
struct Property {};

#define SPECIFY_PROPERTY_TYPE(Key,Type,UsingName)                     \
    template<>                                                        \
    struct Property<Key>                                              \
    {                                                                 \
        using type = Type;                                            \
        static constexpr PropertyKey key = Key;                  \
        static constexpr auto init_value = std::pair{key,type{}};     \
    };                                                                \
    using UsingName = Property<Key>;                                  \

}