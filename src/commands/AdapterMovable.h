#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractMovable
{
public:

    virtual PositionProperty::type getPosition() const = 0;
    virtual void setPosition(const PositionProperty::type &value) = 0;
    virtual VelocityRotateProperty::type getVelocity() const = 0;

    virtual AbstractObjectPtr getObject() const = 0;
};

using AbstractMovablePtr = std::shared_ptr<AbstractMovable>;

class AdapterMovable : public AbstractMovable
{
public:
    
    explicit AdapterMovable(const AbstractObjectPtr &obj);
    
    PositionProperty::type getPosition() const override;
    void setPosition(const PositionProperty::type &value) override;
    VelocityRotateProperty::type getVelocity() const override;
    AbstractObjectPtr getObject() const override;

private:
    AbstractObjectPtr m_obj;
};

}