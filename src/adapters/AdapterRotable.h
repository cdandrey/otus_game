#pragma once

#include "AbstractAdapter.h"

namespace otg {

class AbstractAdapterRotable : public AbstractAdapter
{
public:
	explicit AbstractAdapterRotable(const AbstractObjectPtr &object);
	virtual ~AbstractAdapterRotable() = default;

	virtual Result<DirectionProperty::type> getDirection() const = 0;
	virtual Result<void> setDirection(const DirectionProperty::type &value) = 0;
	virtual Result<VelocityRotateProperty::type> getVelocityRotate() const = 0;
};

using AbstractAdapterRotablePtr = std::shared_ptr<AbstractAdapterRotable>;

class AdapterRotable : public AbstractAdapterRotable
{
public:
	explicit AdapterRotable(const AbstractObjectPtr &object);

	Result<DirectionProperty::type> getDirection() const override;
	Result<void> setDirection(const DirectionProperty::type &value) override;
	Result<VelocityRotateProperty::type> getVelocityRotate() const override;
};

}  // namespace otg