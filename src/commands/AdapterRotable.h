#pragma once

#include "AbstractAdapter.h"

namespace otg {

class AbstractAdapterRotable : public AbstractAdapter
{
public:
	explicit AbstractAdapterRotable(const AbstractObjectPtr &object);
	virtual ~AbstractAdapterRotable() = default;

	virtual ResultGet<DirectionProperty::type> getDirection() const = 0;
	virtual ResultSet setDirection(const DirectionProperty::type &value) = 0;
	virtual ResultGet<VelocityRotateProperty::type> getVelocityRotate() const = 0;
};

using AbstractAdapterRotablePtr = std::shared_ptr<AbstractAdapterRotable>;

class AdapterRotable : public AbstractAdapterRotable
{
public:
	explicit AdapterRotable(const AbstractObjectPtr &object);

	ResultGet<DirectionProperty::type> getDirection() const override;
	ResultSet setDirection(const DirectionProperty::type &value) override;
	ResultGet<VelocityRotateProperty::type> getVelocityRotate() const override;
};

}  // namespace otg