#pragma once

#include <expected/expected.h>

namespace otg {

enum class ExceptionErrorType
{
	Missing,
	BadCast,
	NotInitialized,
	Unknown
};

class ExceptionError : public std::exception
{
public:
	explicit ExceptionError(const ExceptionErrorType &type, const std::string &message = {});

	const char *what() const noexcept override;

	std::string errorMessage() const;
	ExceptionErrorType errorType() const;

private:
	ExceptionErrorType m_type = ExceptionErrorType::Unknown;
	std::string m_message = "";
};

tl::unexpected<ExceptionError> makeUnexpected(const ExceptionErrorType &type, const std::string &message = {});

}  // namespace otg