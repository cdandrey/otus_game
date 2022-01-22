#include "CommandMovable.h"

namespace otg {

CommandMovable::CommandMovable(const AbstractAdapterMovablePtr& movable)
    : m_movable{ movable }
{
}

Result<void> CommandMovable::execute()
{
    const auto onGetVelocity = [this](const PositionProperty::type& position) -> Result<void> {
        const auto onSetPosition = [this, &position](const VelocityProperty::type& velocity) -> Result<void> {
            return m_movable->setPosition({ position.x + velocity.dx,position.y + velocity.dy });
        };
        return m_movable->getVelocity().and_then(onSetPosition);
    };
    return m_movable->getPosition().and_then(onGetVelocity);
}

}  // namespace otg