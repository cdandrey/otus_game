#include "AbstractAdapter.h"

namespace otg {

AbstractAdapter::AbstractAdapter(const AbstractObjectPtr &object)
    : m_object {object}
{
}

AbstractAdapter::~AbstractAdapter()
{
}

void AbstractAdapter::setObject(const AbstractObjectPtr &object)
{
	if (m_object != object) {
		m_object = object;
	}
}

Result<AbstractObjectPtr> AbstractAdapter::getObject() const
{
	if (m_object != nullptr) {
		return m_object;
	}

	return makeUnexpected(ExceptionErrorType::NotInitialized, std::string {"Object of adapter is not initialized"});
}

}  // namespace otg
