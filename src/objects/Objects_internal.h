#pragma once

namespace otg {

class AbstractObject;

#define SPECIFY_OBJECT(ObjectName)              \
    class ObjectName : public AbstractObject    \
    {                                           \
        public:                                 \
            ObjectName();                       \
    };                                          \

}