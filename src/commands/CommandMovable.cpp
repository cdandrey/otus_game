#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractMovablePtr &movable)
    : m_movable {movable}
{
}

PropertyResultSet CommandMovable::execute()
{
	const auto onSuccess = [](std::true_type) {
		return std::true_type {};
	};

	const auto onError = [](const PropertyError &error) {
		return PropertyError {error.errorType(), error.errorMessage()};
	};

	const auto getVelocity = [&](const PositionProperty::type &position) {
		const auto setPosition = [&](const VelocityProperty::type &velocity) {
			return m_movable->setPosition(position + velocity).map(onSuccess).map_error(onError);
		};

		return m_movable->getVelocity().and_then(setPosition).map_error(onError);
	};

	return m_movable->getPosition().and_then(getVelocity).map_error(onError);
}

void CommandMovable::set(const AbstractMovablePtr &movable)
{
	if (m_movable != movable) {
		m_movable = movable;
	}
}

}  // namespace otg