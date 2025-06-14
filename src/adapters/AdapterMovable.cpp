#include "AdapterMovable.h"

#include <variant>

namespace otg {

AdapterMovable::AdapterMovable(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
{
}

Result<PositionProperty::type> AdapterMovable::getPosition() const
{
    return AbstractAdapterPositionPropertyGetter::getPosition();
}

Result<void> AdapterMovable::setPosition(const PositionProperty::type& value)
{
    return AbstractAdapterPositionPropertySetter::setPosition(value);
}

Result<VelocityProperty::type> AdapterMovable::getVelocity() const
{
    return AbstractAdapterVelocityPropertyGetter::getVelocity();
}

}  // namespace otg