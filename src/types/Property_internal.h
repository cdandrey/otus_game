
#pragma once

#include "PropertyError.h"

namespace otg {

using PropertyKey = std::string_view;
using PropertyValue = std::any;

template<const PropertyKey &key>
struct Property
{
};

#define SPECIFY_PROPERTY_TYPE(Key, Type, UsingName)                                                                                                            \
	template<>                                                                                                                                                 \
	struct Property<Key>                                                                                                                                       \
	{                                                                                                                                                          \
		using type = Type;                                                                                                                                     \
		using type_expected = tl::expected<type, PropertyError>;                                                                                               \
		static constexpr PropertyKey key = Key;                                                                                                                \
		static type_expected cast(PropertyValue value)                                                                                                         \
		{                                                                                                                                                      \
			try {                                                                                                                                              \
				return std::any_cast<type>(value);                                                                                                             \
			} catch (std::bad_any_cast & e) {                                                                                                                  \
				throw makePropertyUnexpected(PropertyErrorType::BadCast, e.what());                                                                            \
			}                                                                                                                                                  \
		}                                                                                                                                                      \
	};                                                                                                                                                         \
	using UsingName = Property<Key>;

}  // namespace otg