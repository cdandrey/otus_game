#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractRotable
{
public:
	virtual ~AbstractRotable() = default;

	virtual DirectionProperty::type_expected getDirection() const = 0;
	virtual PropertyResultSet setDirection(const DirectionProperty::type &value) = 0;
	virtual VelocityRotateProperty::type_expected getVelocityRotate() const = 0;
};

using AbstractRotablePtr = std::shared_ptr<AbstractRotable>;

class AdapterRotable : public AbstractRotable
{
public:
	explicit AdapterRotable(const AbstractObjectPtr &obj);

	DirectionProperty::type_expected getDirection() const override;
	PropertyResultSet setDirection(const DirectionProperty::type &value) override;
	VelocityRotateProperty::type_expected getVelocityRotate() const override;

private:
	AbstractObjectPtr m_obj;
};

}  // namespace otg