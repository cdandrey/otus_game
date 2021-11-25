#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractAdapterRotablePtr &rotable)
    : m_rotable {rotable}
{
}

ResultSet CommandRotable::execute()
{
	const auto onGetVelocityRotate = [this](const DirectionProperty::type &position) -> ResultSet {
		const auto onSetDirection = [this, &position](const VelocityRotateProperty::type &velocity) -> ResultSet {
			return m_rotable->setDirection(position + velocity);
		};
		return m_rotable->getVelocityRotate().and_then(onSetDirection);
	};
	return m_rotable->getDirection().and_then(onGetVelocityRotate);
}

}  // namespace otg