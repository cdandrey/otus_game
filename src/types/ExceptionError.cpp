#include "ExceptionError.h"

namespace otg {

ExceptionError::ExceptionError(const ExceptionErrorType &type, const std::string &message)
    : m_type(type)
    , m_message(message)
{
}

const char *ExceptionError::what() const noexcept
{
	return m_message.c_str();
}

ExceptionErrorType ExceptionError::errorType() const
{
	return m_type;
}

std::string ExceptionError::errorMessage() const
{
	return m_message;
}

tl::unexpected<ExceptionError> makeUnexpected(const ExceptionErrorType &type, const std::string &message)
{
	return tl::make_unexpected(ExceptionError {type, message});
}

}  // namespace otg