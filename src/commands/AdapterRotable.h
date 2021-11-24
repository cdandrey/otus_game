#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractRotable
{
public:
	explicit AbstractRotable(const AbstractObjectPtr &object);
	virtual ~AbstractRotable() = default;

	virtual DirectionProperty::type_expected getDirection() const = 0;
	virtual PropertyResultSet setDirection(const DirectionProperty::type &value) = 0;
	virtual VelocityRotateProperty::type_expected getVelocityRotate() const = 0;

	void setObject(const AbstractObjectPtr &object);

protected:
	ObjectResultGet getObject() const;

private:
	AbstractObjectPtr m_object;
};

using AbstractRotablePtr = std::shared_ptr<AbstractRotable>;
using AdapapterRotableResultGet = tl::expected<AbstractRotablePtr, ExceptionError>;

class AdapterRotable : public AbstractRotable
{
public:
	explicit AdapterRotable(const AbstractObjectPtr &object);

	DirectionProperty::type_expected getDirection() const override;
	PropertyResultSet setDirection(const DirectionProperty::type &value) override;
	VelocityRotateProperty::type_expected getVelocityRotate() const override;
};

}  // namespace otg