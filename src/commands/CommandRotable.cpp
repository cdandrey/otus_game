#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable {rotable}
{
}

PropertyResultSet CommandRotable::execute()
{
	const auto onSuccess = [](std::true_type) -> std::true_type {
		return {};
	};

	const auto getVelocityRotate = [this, &onSuccess](const PositionProperty::type &position) {
		const auto setDirection = [this, &onSuccess, &position](const VelocityProperty::type &velocity) {
			return m_rotable->setDirection(position + velocity).map(onSuccess);
		};

		return m_rotable->getVelocityRotate().and_then(setDirection);
	};

	return m_rotable->getDirection().and_then(getVelocityRotate);
}

void CommandRotable::set(const AbstractRotablePtr &rotable)
{
	if (m_rotable != rotable) {
		m_rotable = rotable;
	}
}

}  // namespace otg