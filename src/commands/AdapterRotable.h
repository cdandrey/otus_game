#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractRotable
{
public:
	explicit AbstractRotable(const AbstractObjectPtr &object);
	virtual ~AbstractRotable() = default;

	virtual ResultGet<DirectionProperty::type> getDirection() const = 0;
	virtual ResultSet setDirection(const DirectionProperty::type &value) = 0;
	virtual ResultGet<VelocityRotateProperty::type> getVelocityRotate() const = 0;

	void setObject(const AbstractObjectPtr &object);

protected:
	ResultGet<AbstractObjectPtr> getObject() const;

private:
	AbstractObjectPtr m_object;
};

using AbstractRotablePtr = std::shared_ptr<AbstractRotable>;

class AdapterRotable : public AbstractRotable
{
public:
	explicit AdapterRotable(const AbstractObjectPtr &object);

	ResultGet<DirectionProperty::type> getDirection() const override;
	ResultSet setDirection(const DirectionProperty::type &value) override;
	ResultGet<VelocityRotateProperty::type> getVelocityRotate() const override;
};

}  // namespace otg