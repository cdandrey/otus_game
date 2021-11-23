#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable {rotable}
{
}

CommandResult CommandRotable::execute()
{
	const auto onSuccess = [](std::true_type) {
		return std::true_type {};
	};

	const auto onError = [](const PropertyError &error) {
		return PropertyError {error.errorType(), error.errorMessage()};
	};

	const auto onGetVelocityRotate = [&](const PositionProperty::type &position) {
		const auto onSetDirection = [&](const VelocityProperty::type &velocity) {
			return m_rotable->setDirection(position + velocity).map(onSuccess).map_error(onError);
		};

		return m_rotable->getVelocityRotate().and_then(onSetDirection).map_error(onError);
	};

	return m_rotable->getDirection().and_then(onGetVelocityRotate).map_error(onError);
}

}  // namespace otg