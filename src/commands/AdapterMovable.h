#pragma once

#include <memory>

#include "../objects/Objects.h"

namespace otg {

class AbstractMovable
{
public:
	explicit AbstractMovable(const AbstractObjectPtr &object);
	virtual ~AbstractMovable() = default;

	virtual PositionProperty::type_expected getPosition() const = 0;
	virtual PropertyResultSet setPosition(const PositionProperty::type &value) = 0;
	virtual VelocityRotateProperty::type_expected getVelocity() const = 0;

	void setObject(const AbstractObjectPtr &object);

protected:
	ObjectResultGet getObject() const;

private:
	AbstractObjectPtr m_object;
};

using AbstractMovablePtr = std::shared_ptr<AbstractMovable>;
using AdapterMovableResultGet = tl::expected<AbstractMovablePtr, ExceptionError>;

class AdapterMovable : public AbstractMovable
{
public:
	explicit AdapterMovable(const AbstractObjectPtr &object);

	PositionProperty::type_expected getPosition() const override;
	PropertyResultSet setPosition(const PositionProperty::type &value) override;
	VelocityRotateProperty::type_expected getVelocity() const override;
};

}  // namespace otg