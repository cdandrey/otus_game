#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractAdapterRotablePtr& rotable)
    : m_rotable{ rotable }
{
}

Result<void> CommandRotable::execute()
{
    const auto onGetVelocityRotate = [this](const DirectionProperty::type& position) -> Result<void> {
        const auto onSetDirection = [this, &position](const VelocityRotateProperty::type& velocity) -> Result<void> {
            return m_rotable->setDirection({ position.x + velocity.dx,position.y + velocity.dy });
        };
        return m_rotable->getVelocityRotate().and_then(onSetDirection);
    };
    return m_rotable->getDirection().and_then(onGetVelocityRotate);
}

}  // namespace otg