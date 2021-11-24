#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractMovablePtr &movable)
    : m_movable {movable}
{
}

PropertyResultSet CommandMovable::execute()
{
	const auto onSuccess = [](std::true_type) -> std::true_type {
		return {};
	};

	const auto getVelocity = [this, &onSuccess](const PositionProperty::type &position) {
		const auto setPosition = [this, &onSuccess, &position](const VelocityProperty::type &velocity) {
			return m_movable->setPosition(position + velocity).map(onSuccess);
		};

		return m_movable->getVelocity().and_then(setPosition);
	};

	return m_movable->getPosition().and_then(getVelocity);
}

void CommandMovable::set(const AbstractMovablePtr &movable)
{
	if (m_movable != movable) {
		m_movable = movable;
	}
}

}  // namespace otg