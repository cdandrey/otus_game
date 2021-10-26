#pragma once

#include "../objects/Objects.h"

namespace otg {

class AbstractMovable
{
public:

    virtual PositionProperty::type getPosition() const = 0;
    virtual void setPosition(const PositionProperty::type& value) = 0;
    virtual VelocityProperty::type getVelocity() const = 0;
};

using AbstractMovablePtr = std::shared_ptr<AbstractMovable>;

class AdapterMovable : public AbstractMovable
{
public:
    
    explicit AdapterMovable(const ObjectBasePtr& obj);
    
    PositionProperty::type getPosition() const override;
    void setPosition(const PositionProperty::type& value) override;
    VelocityProperty::type getVelocity() const override;

private:
    ObjectBasePtr m_obj;
};

}