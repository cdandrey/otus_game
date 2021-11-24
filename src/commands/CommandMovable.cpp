#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractMovablePtr &movable)
    : m_movable {movable}
{
}

PropertyResultSet CommandMovable::execute()
{
	const auto onGetPosition = [](const AbstractMovablePtr &movable) -> PropertyResultSet {
		const auto onGetVelocity = [&movable](const PositionProperty::type &position) -> PropertyResultSet {
			const auto onSetPosition = [&movable, &position](const VelocityProperty::type &velocity) -> PropertyResultSet {
				return movable->setPosition(position + velocity);
			};

			return movable->getVelocity().and_then(onSetPosition);
		};

		return movable->getPosition().and_then(onGetVelocity);
	};

	return getAdapter().and_then(onGetPosition);
}

void CommandMovable::setAdapter(const AbstractMovablePtr &movable)
{
	if (m_movable != movable) {
		m_movable = movable;
	}
}

AdapterMovableResultGet CommandMovable::getAdapter() const
{
	if (m_movable != nullptr) {
		return m_movable;
	}

	return makePropertyUnexpected(PropertyErrorType::NotInitialized, std::string {"Adapter of movable command is not initialized"});
}

}  // namespace otg