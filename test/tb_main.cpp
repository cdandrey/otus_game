#include <gtest/gtest.h>

#include "../src/objects/Objects.cpp"
#include "../src/types/Vector.cpp"
#include "../src/commands/AdapterMovable.cpp"
#include "../src/commands/AdapterRotable.cpp"
#include "../src/commands/CommandMovable.cpp"
#include "../src/commands/CommandRotable.cpp"

namespace detail {

using PropertyHas = std::unordered_map<otg::PropertyKey,bool>;

void checkPropertyInit(const otg::AbstractObjectPtr& obj,const PropertyHas &hasProperty) 
{
    using namespace otg;

    const auto position = obj->getProperty(PropertyKey::Position);
    const auto velocity = obj->getProperty(PropertyKey::Velocity);
    const auto health = obj->getProperty(PropertyKey::Health);
    const auto fuel = obj->getProperty(PropertyKey::Fuel);
    const auto ammo = obj->getProperty(PropertyKey::Ammo);

    EXPECT_EQ(position.has_value(),hasProperty.at(PropertyKey::Position));
    EXPECT_EQ(velocity.has_value(),hasProperty.at(PropertyKey::Velocity));
    EXPECT_EQ(health.has_value(),hasProperty.at(PropertyKey::Health));
    EXPECT_EQ(fuel.has_value(),hasProperty.at(PropertyKey::Fuel));
    EXPECT_EQ(ammo.has_value(),hasProperty.at(PropertyKey::Ammo));
}

}

TEST(tb_main,objectBunkerInit)
{
    const auto obj = std::make_shared<otg::ObjectBunker>();
    detail::PropertyHas property{{otg::PropertyKey::Position,true},
                                 {otg::PropertyKey::Velocity,false},
                                 {otg::PropertyKey::Health,true},
                                 {otg::PropertyKey::Fuel,true},
                                 {otg::PropertyKey::Ammo,true}};

    detail::checkPropertyInit(obj,property);
}

TEST(tb_main,objectTankInit)
{
    const auto obj = std::make_shared<otg::ObjectTank>();
    detail::PropertyHas property{{otg::PropertyKey::Position,true},
                                 {otg::PropertyKey::Velocity,true},
                                 {otg::PropertyKey::Health,true},
                                 {otg::PropertyKey::Fuel,true},
                                 {otg::PropertyKey::Ammo,true}};
    
    detail::checkPropertyInit(obj,property);
}

TEST(tb_main,move)
{
    using namespace otg;

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();
    
    tank->setProperty(PropertyKey::Position,Vector{12,5,0});
    tank->setProperty(PropertyKey::Velocity,Vector{-7,3,0});

    AbstractMovablePtr adapterMove = std::make_shared<AdapterMovable>(tank);
    AbstractCommandPtr commandMove = std::make_shared<CommandMovable>(adapterMove);
    tank = commandMove->execute();

    const Vector expectPosition{5,8,0};
    
    try {
        const auto actualPosition = std::get<Vector>(tank->getProperty(PropertyKey::Position).value_or(Vector{-1,-1,-1}));
        EXPECT_EQ(actualPosition,expectPosition);
    }
    catch (std::bad_variant_access&) {
        FAIL() << "Invalid property type";
    }
}

TEST(tb_main,rotate)
{
    using namespace otg;

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();
    
    tank->setProperty(PropertyKey::Direction,DirectionProperty::type{0,1,0});
    tank->setProperty(PropertyKey::VelocityRotate,VelocityRotateProperty::type{1,0,0});

    AbstractRotablePtr adapterRotate = std::make_shared<AdapterRotable>(tank);
    AbstractCommandPtr commandRotate = std::make_shared<CommandRotable>(adapterRotate);
    tank = commandRotate->execute();

    const DirectionProperty::type expectDirection{1,1,0};
    
    try {
        const auto actualDirection = std::get<DirectionProperty::type>(tank->getProperty(PropertyKey::Direction).value_or(DirectionProperty::type{0,0,0}));
        EXPECT_EQ(actualDirection,expectDirection);
    }
    catch (std::bad_variant_access&) {
        FAIL() << "Invalid property type";
    }
}

int main (int argc,char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}
