#include <iostream>

#include "objects/Objects.h"
#include "commands/CommandMovable.h"

int main (int, char **)
{
    using namespace otg;

    std::cout << "Start game..." << std::endl;

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();

    int x;
    int y;

    std::cout << "Set tank position (x,y)" << std::endl;
    std::cin >> x >> y;
    
    tank->setProperty(PositionProperty::key,Vector{x,y,0});
    std::cout << "Tank position: " << std::any_cast<Vector>(tank->getProperty(PositionProperty::key).value()).toString() << std::endl;

    std::cout << "set tank velocity (dx,dy)" << std::endl;
    std::cin >> x >> y;

    tank->setProperty(VelocityProperty::key,Vector{x,y,0});
    std::cout << "Tank velocity: " << std::any_cast<Vector>(tank->getProperty(VelocityProperty::key).value()).toString() << std::endl;

    std::cout << "Move tank..." << std::endl;

    AbstractMovablePtr adapterMove = std::make_shared<AdapterMovable>(tank);
    AbstractCommandPtr commandMove = std::make_shared<CommandMovable>(adapterMove);
    tank = commandMove->execute();

    std::cout << "Tank position: " << std::any_cast<Vector>(tank->getProperty(PositionProperty::key).value()).toString() << std::endl;
    std::cout << "End game" << std::endl;

    return 0;
}
