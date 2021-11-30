#pragma once

#include "../objects/Objects.h"

namespace otg {

class AbstractAdapter
{
public:
	explicit AbstractAdapter(const AbstractObjectPtr &object);
	virtual ~AbstractAdapter() = 0;

	void setObject(const AbstractObjectPtr &object);

protected:
	ResultGet<AbstractObjectPtr> getObject() const;

private:
	AbstractObjectPtr m_object;
};

}  // namespace otg