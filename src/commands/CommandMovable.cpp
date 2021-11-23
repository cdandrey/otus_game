#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractMovablePtr &movable)
    : m_movable {movable}
{
}

CommandResult CommandMovable::execute()
{
	const auto onSuccess = [](std::true_type) {
		return std::true_type {};
	};

	const auto onError = [](const PropertyError &error) {
		return PropertyError {error.errorType(), error.errorMessage()};
	};

	const auto onGetVelocity = [&](const PositionProperty::type &position) {
		const auto onSetPosition = [&](const VelocityProperty::type &velocity) {
			return m_movable->setPosition(position + velocity).map(onSuccess).map_error(onError);
		};

		return m_movable->getVelocity().and_then(onSetPosition).map_error(onError);
	};

	return m_movable->getPosition().and_then(onGetVelocity).map_error(onError);
}

}  // namespace otg