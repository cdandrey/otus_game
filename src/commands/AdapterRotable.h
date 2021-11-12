#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractRotable
{
public:

    virtual ~AbstractRotable() = default;

    virtual DirectionProperty::type getDirection() const = 0;
    virtual void setDirection(const DirectionProperty::type &value) = 0;
    virtual VelocityRotateProperty::type getVelocityRotate() const = 0;
};

using AbstractRotablePtr = std::shared_ptr<AbstractRotable>;

class AdapterRotable : public AbstractRotable
{
public:
    
    explicit AdapterRotable(const AbstractObjectPtr &obj);
    
    DirectionProperty::type getDirection() const override;
    void setDirection(const DirectionProperty::type &value) override;
    VelocityRotateProperty::type getVelocityRotate() const override;

private:
    AbstractObjectPtr m_obj;
};

}