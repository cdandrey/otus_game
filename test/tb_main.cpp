#include <gtest/gtest.h>

#include "../src/objects/Objects.cpp"
#include "../src/types/Vector.cpp"
#include "../src/commands/AdapterMovable.cpp"
#include "../src/commands/AdapterRotable.cpp"
#include "../src/commands/CommandMovable.cpp"
#include "../src/commands/CommandRotable.cpp"

namespace detail {

const std::vector<otg::PropertyKey> listPropertys {
    otg::PositionProperty::key,
    otg::VelocityProperty::key,
    otg::HealthProperty::key,
    otg::FuelProperty::key,
    otg::AmmoProperty::key,
    otg::DirectionProperty::key,
    otg::VelocityRotateProperty::key
};

using PropertyHas = std::unordered_map<otg::PropertyKey,bool>;

void checkPropertyInit(const otg::AbstractObjectPtr& obj,const PropertyHas &hasProperty) 
{
    using namespace otg;

    for (auto key : listPropertys) {
        EXPECT_EQ(obj->getProperty(key).has_value(),hasProperty.at(key)) << "PropertyKey: " << std::string{key};
    } 
}

}

TEST(tb_main,objectBunkerInit)
{
    const auto obj = std::make_shared<otg::ObjectBunker>();
    detail::PropertyHas property{{otg::PositionProperty::key,true},
                                 {otg::VelocityProperty::key,false},
                                 {otg::HealthProperty::key,true},
                                 {otg::FuelProperty::key,true},
                                 {otg::AmmoProperty::key,true},
                                 {otg::DirectionProperty::key,true},
                                 {otg::VelocityRotateProperty::key,false}};

    detail::checkPropertyInit(obj,property);
}

TEST(tb_main,objectTankInit)
{
    const auto obj = std::make_shared<otg::ObjectTank>();
    detail::PropertyHas property{{otg::PositionProperty::key,true},
                                 {otg::VelocityProperty::key,true},
                                 {otg::HealthProperty::key,true},
                                 {otg::FuelProperty::key,true},
                                 {otg::AmmoProperty::key,true},
                                 {otg::DirectionProperty::key,true},
                                 {otg::VelocityRotateProperty::key,true}};

    
    detail::checkPropertyInit(obj,property);
}

TEST(tb_main,objectTreeInit)
{
    const auto obj = std::make_shared<otg::ObjectTree>();
    detail::PropertyHas property{{otg::PositionProperty::key,true},
                                 {otg::VelocityProperty::key,false},
                                 {otg::HealthProperty::key,true},
                                 {otg::FuelProperty::key,false},
                                 {otg::AmmoProperty::key,false},
                                 {otg::DirectionProperty::key,false},
                                 {otg::VelocityRotateProperty::key,false}};
    
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
    commandMove->execute();

    const Vector expectPosition{5,8,0};
    
    using Type = PositionProperty::type;
    const auto actualPosition = tank->extractPropertyValue<Type>(tank->getProperty(PositionProperty::key));

    ::testing::StaticAssertTypeEq<decltype(expectPosition), decltype(actualPosition)>();
    EXPECT_EQ(actualPosition,expectPosition);
}

TEST(tb_main,rotate)
{
    using namespace otg;

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();
    
    tank->setProperty(DirectionProperty::key,DirectionProperty::type{0,1,0});
    tank->setProperty(VelocityRotateProperty::key,VelocityRotateProperty::type{1,0,0});

    AbstractRotablePtr adapterRotate = std::make_shared<AdapterRotable>(tank);
    AbstractCommandPtr commandRotate = std::make_shared<CommandRotable>(adapterRotate);
    commandRotate->execute();

    const Vector expectDirection{1,1,0};
    
    using Type = DirectionProperty::type;
    const auto actualDirection = tank->extractPropertyValue<Type>(tank->getProperty(DirectionProperty::key).value_or(DirectionProperty::type{0,0,0}));

    ::testing::StaticAssertTypeEq<decltype(expectDirection), decltype(actualDirection)>();
    EXPECT_EQ(actualDirection,expectDirection);
}

int main (int argc,char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}
