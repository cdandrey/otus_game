#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable {rotable}
{
}

PropertyResultSet CommandRotable::execute()
{
	const auto onGetDirection = [](const AbstractRotablePtr &rotable) -> PropertyResultSet {
		const auto onGetVelocityRotate = [&rotable](const DirectionProperty::type &position) -> PropertyResultSet {
			const auto onSetDirection = [&rotable, &position](const VelocityRotateProperty::type &velocity) -> PropertyResultSet {
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

AdapapterRotableResultGet CommandRotable::getAdapter() const
{
	if (m_rotable != nullptr) {
		return m_rotable;
	}

	return makePropertyUnexpected(PropertyErrorType::NotInitialized, std::string {"Adapter of rotable command is not initialized"});
}

}  // namespace otg