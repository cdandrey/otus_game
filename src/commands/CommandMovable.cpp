#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractMovablePtr &movable)
    : m_movable {movable}
{
}

ResultSet CommandMovable::execute()
{
	const auto onGetPosition = [](const AbstractMovablePtr &movable) -> ResultSet {
		const auto onGetVelocity = [&movable](const PositionProperty::type &position) -> ResultSet {
			const auto onSetPosition = [&movable, &position](const VelocityProperty::type &velocity) -> ResultSet {
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

ResultGet<AbstractMovablePtr> CommandMovable::getAdapter() const
{
	if (m_movable != nullptr) {
		return m_movable;
	}

	return makeUnexpected(ExceptionErrorType::NotInitialized, std::string {"Adapter of movable command is not initialized"});
}

}  // namespace otg