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

    const auto position = obj->getProperty(PositionProperty::key);
    const auto velocity = obj->getProperty(VelocityProperty::key);
    const auto health = obj->getProperty(HealthProperty::key);
    const auto fuel = obj->getProperty(FuelProperty::key);
    const auto ammo = obj->getProperty(AmmoProperty::key);

    EXPECT_EQ(position.has_value(),hasProperty.at(PositionProperty::key));
    EXPECT_EQ(velocity.has_value(),hasProperty.at(VelocityProperty::key));
    EXPECT_EQ(health.has_value(),hasProperty.at(HealthProperty::key));
    EXPECT_EQ(fuel.has_value(),hasProperty.at(FuelProperty::key));
    EXPECT_EQ(ammo.has_value(),hasProperty.at(AmmoProperty::key));
}

}

TEST(tb_main,objectBunkerInit)
{
    const auto obj = std::make_shared<otg::ObjectBunker>();
    detail::PropertyHas property{{otg::PositionProperty::key,true},
                                 {otg::VelocityProperty::key,false},
                                 {otg::HealthProperty::key,true},
                                 {otg::FuelProperty::key,true},
                                 {otg::AmmoProperty::key,true}};

    detail::checkPropertyInit(obj,property);
}

TEST(tb_main,objectTankInit)
{
    const auto obj = std::make_shared<otg::ObjectTank>();
    detail::PropertyHas property{{otg::PositionProperty::key,true},
                                 {otg::VelocityProperty::key,true},
                                 {otg::HealthProperty::key,true},
                                 {otg::FuelProperty::key,true},
                                 {otg::AmmoProperty::key,true}};
    
    detail::checkPropertyInit(obj,property);
}

TEST(tb_main,move)
{
    using namespace otg;

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();
    
    tank->setProperty(PositionProperty::key,Vector{12,5,0});
    tank->setProperty(VelocityProperty::key,Vector{-7,3,0});

    AbstractMovablePtr adapterMove = std::make_shared<AdapterMovable>(tank);
    AbstractCommandPtr commandMove = std::make_shared<CommandMovable>(adapterMove);
    tank = commandMove->execute();

    const Vector expectPosition{5,8,0};
    
    try {
        const auto actualPosition = std::any_cast<Vector>(tank->getProperty(PositionProperty::key).value_or(Vector{-1,-1,-1}));
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
    
    tank->setProperty(DirectionProperty::key,DirectionProperty::type{0,1,0});
    tank->setProperty(VelocityRotateProperty::key,VelocityRotateProperty::type{1,0,0});

    AbstractRotablePtr adapterRotate = std::make_shared<AdapterRotable>(tank);
    AbstractCommandPtr commandRotate = std::make_shared<CommandRotable>(adapterRotate);
    tank = commandRotate->execute();

    const DirectionProperty::type expectDirection{1,1,0};
    
    try {
        const auto actualDirection = std::any_cast<DirectionProperty::type>(tank->getProperty(DirectionProperty::key).value_or(DirectionProperty::type{0,0,0}));
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
