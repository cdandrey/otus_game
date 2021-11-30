#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractAdapterMovablePtr &movable)
    : m_movable {movable}
{
}

ResultSet CommandMovable::execute()
{
	const auto onGetVelocity = [this](const PositionProperty::type &position) -> ResultSet {
		const auto onSetPosition = [this, &position](const VelocityProperty::type &velocity) -> ResultSet {
			return m_movable->setPosition(position + velocity);
		};
		return m_movable->getVelocity().and_then(onSetPosition);
	};
	return m_movable->getPosition().and_then(onGetVelocity);
}

}  // namespace otg