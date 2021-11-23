#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractMovable
{
public:
	virtual ~AbstractMovable() = default;

	virtual PositionProperty::type_expected getPosition() const = 0;
	virtual PropertyResultSet setPosition(const PositionProperty::type &value) = 0;
	virtual VelocityRotateProperty::type_expected getVelocity() const = 0;
};

using AbstractMovablePtr = std::shared_ptr<AbstractMovable>;

class AdapterMovable : public AbstractMovable
{
public:
	explicit AdapterMovable(const AbstractObjectPtr &obj);

	PositionProperty::type_expected getPosition() const override;
	PropertyResultSet setPosition(const PositionProperty::type &value) override;
	VelocityRotateProperty::type_expected getVelocity() const override;

private:
	AbstractObjectPtr m_obj;
};

}  // namespace otg