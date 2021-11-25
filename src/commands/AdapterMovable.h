#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractMovable
{
public:
	explicit AbstractMovable(const AbstractObjectPtr &object);
	virtual ~AbstractMovable() = default;

	virtual ResultGet<PositionProperty::type> getPosition() const = 0;
	virtual ResultSet setPosition(const PositionProperty::type &value) = 0;
	virtual ResultGet<VelocityProperty::type> getVelocity() const = 0;

	void setObject(const AbstractObjectPtr &object);

protected:
	ResultGet<AbstractObjectPtr> getObject() const;

private:
	AbstractObjectPtr m_object;
};

using AbstractMovablePtr = std::shared_ptr<AbstractMovable>;

class AdapterMovable : public AbstractMovable
{
public:
	explicit AdapterMovable(const AbstractObjectPtr &object);

	ResultGet<PositionProperty::type> getPosition() const override;
	ResultSet setPosition(const PositionProperty::type &value) override;
	ResultGet<VelocityProperty::type> getVelocity() const override;
};

}  // namespace otg