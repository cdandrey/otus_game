#pragma once

#include <expected/expected.h>

namespace otg {

enum class PropertyErrorType
{
	Missing,
	BadCast,
	NotInitialized,
	Unknown
};

class PropertyError : public std::exception
{
public:
	explicit PropertyError(const PropertyErrorType &type, const std::string &message = {});

	const char *what() const noexcept override;

	std::string errorMessage() const;
	PropertyErrorType errorType() const;

private:
	PropertyErrorType m_type = PropertyErrorType::Unknown;
	std::string m_message = "";
};

tl::unexpected<PropertyError> makePropertyUnexpected(const PropertyErrorType &type, const std::string &message = {});

}  // namespace otg