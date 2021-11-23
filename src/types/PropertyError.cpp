#include "PropertyError.h"

namespace otg {

PropertyError::PropertyError(const PropertyErrorType &type, const std::string &message)
    : m_type(type)
    , m_message(message)
{
}

const char *PropertyError::what() const noexcept
{
	return m_message.c_str();
}

PropertyErrorType PropertyError::errorType() const
{
	return m_type;
}

std::string PropertyError::errorMessage() const
{
	return m_message;
}

tl::unexpected<PropertyError> makePropertyUnexpected(const PropertyErrorType &type, const std::string &message)
{
	return tl::make_unexpected(PropertyError {type, message});
}

}  // namespace otg