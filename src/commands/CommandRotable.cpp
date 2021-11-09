#include "CommandRotable.h"

namespace otg {

CommandRotable::CommandRotable(const AbstractRotablePtr &rotable)
    : m_rotable{rotable}
{}

AbstractObjectPtr CommandRotable::execute()
{
    m_rotable->setDirection(m_rotable->getDirection() + m_rotable->getVelocityRotate());
    return m_rotable->getObject();
}

}