#pragma once

#include <string>
#include <expected.h>

namespace otg {

enum class ExceptionErrorType
{
    Missing,
    BadCast,
    NotInitialized,
    ExecuteStop,
    ExecuteInterrupt,
    CommandExeption,
    Unknown
};

class ExceptionError : public std::exception
{
public:
    explicit ExceptionError(const ExceptionErrorType& type, const std::string& message = {});

    const char* what() const noexcept override;

    std::string message() const;
    ExceptionErrorType type() const;

private:
    ExceptionErrorType m_type = ExceptionErrorType::Unknown;
    std::string m_message = "";
};

tl::unexpected<ExceptionError> makeUnexpected(const ExceptionErrorType& type, const std::string& message = {});

template<class T>
using Result = tl::expected<T, ExceptionError>;

}  // namespace otg