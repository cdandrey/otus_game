#pragma once

#include "AbstractAdapter.h"

namespace otg {

class AbstractAdapterMovable : public AbstractAdapter
{
public:
	explicit AbstractAdapterMovable(const AbstractObjectPtr &object);
	virtual ~AbstractAdapterMovable() = default;

	virtual ResultGet<PositionProperty::type> getPosition() const = 0;
	virtual ResultSet setPosition(const PositionProperty::type &value) = 0;
	virtual ResultGet<VelocityProperty::type> getVelocity() const = 0;
};

using AbstractAdapterMovablePtr = std::shared_ptr<AbstractAdapterMovable>;

class AdapterMovable : public AbstractAdapterMovable
{
public:
	explicit AdapterMovable(const AbstractObjectPtr &object);

	ResultGet<PositionProperty::type> getPosition() const override;
	ResultSet setPosition(const PositionProperty::type &value) override;
	ResultGet<VelocityProperty::type> getVelocity() const override;
};

}  // namespace otg