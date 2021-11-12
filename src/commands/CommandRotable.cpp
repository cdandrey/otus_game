#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable{rotable}
{}

void CommandRotable::execute()
{
    m_rotable->setDirection(m_rotable->getDirection() + m_rotable->getVelocityRotate());
}

}