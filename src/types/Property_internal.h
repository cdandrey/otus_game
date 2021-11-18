
#pragma once

namespace otg {

using PropertyKey = std::string_view;
using PropertyValue = std::any;

template<const PropertyKey &key>
struct Property {};

#define SPECIFY_PROPERTY_TYPE(Key,Type,UsingName)\
    template<>\
    struct Property<Key>\
    {\
        using type = Type;\
        static constexpr PropertyKey key = Key;\
        static type cast(PropertyValue value)\
        {\
            try {\
                return std::any_cast<type>(value);\
            } catch (std::bad_any_cast&) {\
            }\
            return {};\
        }\
    };\
    using UsingName = Property<Key>;\

}