#include "AbstractAdapter.h"

namespace otg {

AbstractAdapter::AbstractAdapter(const AbstractObjectPtr& object)
    : m_object{ object }
{
}

AbstractAdapter::~AbstractAdapter()
{
}

Result<AbstractObjectPtr> AbstractAdapter::getObject() const
{
    if (m_object != nullptr)
    {
        return m_object;
    }

    return makeUnexpected(ExceptionErrorType::NotInitialized, std::string{ "Object of adapter is not initialized" });
}

}  // namespace otg
