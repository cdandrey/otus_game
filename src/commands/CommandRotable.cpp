#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable {rotable}
{
}

ResultSet CommandRotable::execute()
{
	const auto onGetDirection = [](const AbstractRotablePtr &rotable) -> ResultSet {
		const auto onGetVelocityRotate = [&rotable](const DirectionProperty::type &position) -> ResultSet {
			const auto onSetDirection = [&rotable, &position](const VelocityRotateProperty::type &velocity) -> ResultSet {
				return rotable->setDirection(position + velocity);
			};
			return rotable->getVelocityRotate().and_then(onSetDirection);
		};
		return rotable->getDirection().and_then(onGetVelocityRotate);
	};

	return getAdapter().and_then(onGetDirection);
}

void CommandRotable::setAdapetr(const AbstractRotablePtr &rotable)
{
	if (m_rotable != rotable) {
		m_rotable = rotable;
	}
}

ResultGet<AbstractRotablePtr> CommandRotable::getAdapter() const
{
	if (m_rotable != nullptr) {
		return m_rotable;
	}

	return makeUnexpected(ExceptionErrorType::NotInitialized, std::string {"Adapter of rotable command is not initialized"});
}

}  // namespace otg