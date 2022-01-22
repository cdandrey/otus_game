#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractAdapterRotablePtr& rotable)
    : m_rotable{ rotable }
{
}

Result<void> CommandRotable::execute()
{
    const auto onGetVelocityRotate = [this](const DirectionProperty::type& direction) -> Result<void> {
        const auto onSetDirection = [this, &direction](const VelocityRotateProperty::type& velocityRotate) -> Result<void> {
            return m_rotable->setDirection(direction + velocityRotate.da);
        };
        return m_rotable->getVelocityRotate().and_then(onSetDirection);
    };
    return m_rotable->getDirection().and_then(onGetVelocityRotate);
}

}  // namespace otg