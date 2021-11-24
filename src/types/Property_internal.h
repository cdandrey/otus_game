
#pragma once

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
		using type_expected = tl::expected<type, ExceptionError>;                                                                                              \
		static constexpr PropertyKey key = Key;                                                                                                                \
		static type_expected cast(PropertyValue value)                                                                                                         \
		{                                                                                                                                                      \
			try {                                                                                                                                              \
				return std::any_cast<type>(value);                                                                                                             \
			} catch (std::bad_any_cast & e) {                                                                                                                  \
				return makeUnexpected(ExceptionErrorType::BadCast, e.what());                                                                                  \
			} catch (...) {                                                                                                                                    \
				return makeUnexpected(ExceptionErrorType::Unknown, {"Unknown error of type cast of property " + std::string {Key}});                           \
			}                                                                                                                                                  \
		}                                                                                                                                                      \
	};                                                                                                                                                         \
	using UsingName = Property<Key>;

}  // namespace otg