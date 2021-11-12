#pragma once

#include <memory>

namespace otg {

class AbstractCommand
{
public:
    virtual ~AbstractCommand() = default;

    virtual void execute() = 0;
};

using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

}