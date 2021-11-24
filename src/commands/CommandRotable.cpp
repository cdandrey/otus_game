#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable {rotable}
{
}

PropertyResultSet CommandRotable::execute()
{
	const auto onSuccess = [](std::true_type) {
		return std::true_type {};
	};

	const auto onError = [](const PropertyError &error) {
		return PropertyError {error.errorType(), error.errorMessage()};
	};

	const auto getVelocityRotate = [&](const PositionProperty::type &position) {
		const auto setDirection = [&](const VelocityProperty::type &velocity) {
			return m_rotable->setDirection(position + velocity).map(onSuccess).map_error(onError);
		};

		return m_rotable->getVelocityRotate().and_then(setDirection).map_error(onError);
	};

	return m_rotable->getDirection().and_then(getVelocityRotate).map_error(onError);
}

void CommandRotable::set(const AbstractRotablePtr &rotable)
{
	if (m_rotable != rotable) {
		m_rotable = rotable;
	}
}

}  // namespace otg