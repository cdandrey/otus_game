#include <gtest/gtest.h>
#include <typeinfo>

#include "../src/adapters/AbstractAdapter.cpp"
#include "../src/adapters/AdapterMovable.cpp"
#include "../src/adapters/AdapterRotable.cpp"
#include "../src/commands/CommandInterrupt.cpp"
#include "../src/commands/CommandMovable.cpp"
#include "../src/commands/CommandRotable.cpp"
#include "../src/commands/CommandStop.cpp"
#include "../src/commands/CommandWorker.cpp"
#include "../src/objects/Objects.cpp"
#include "../src/types/ExceptionError.cpp"
#include "../src/types/Point.cpp"
#include "../src/types/VectorVelocity.cpp"
#include "../src/types/Angel.cpp"

namespace detail {

void checkExistingProperty(const otg::AbstractObjectPtr& obj, const otg::PropertyKey& key)
{
    const auto onMissing = [](const otg::ExceptionError& error) {
        FAIL() << error.message();
    };

    const auto onExist = [&obj, &key, &onMissing]() {
        obj->getProperty(key).map_error(onMissing);
        SUCCEED();
    };

    obj->setProperty(key, {}).map(onExist).map_error(onMissing);
}

void checkMissingProperty(const otg::AbstractObjectPtr& obj, const otg::PropertyKey& key)
{
    const std::string errorMessage{ "Property \"" + std::string {key} + "\" exists for object " + std::string {typeid(*obj).name()} };

    const auto onExist = [&errorMessage]() {
        FAIL() << errorMessage;
    };

    const auto onMissing = [&obj, &key, &errorMessage](const otg::ExceptionError&) {
        obj->getProperty(key)
            .map([&errorMessage](const auto&&) {
            FAIL() << errorMessage;
                })
            .map_error([](const otg::ExceptionError&) {
                    SUCCEED();
                });
    };

    obj->setProperty(key, {}).map(onExist).map_error(onMissing);
}

void checkSetProperty(const otg::AbstractObjectPtr& obj, const otg::PropertyKey& key, const otg::PropertyValue& value)
{
    obj->setProperty(key, value)
        .map([]() {
        SUCCEED();
            })
        .map_error([](const otg::ExceptionError& error) {
                FAIL() << error.message();
            });
}

template<class P, class T = P::type>
void checkExecute(const otg::AbstractObjectPtr& obj, otg::AbstractCommandPtr& cmd, const T& expectValue)
{
    using namespace otg;

    const auto onError = [](const ExceptionError& error) {
        FAIL() << error.message();
    };

    const auto onSuccess = [&obj, &expectValue]() {
        const auto onCastSuccess = [&expectValue](const T& actualValue) {
            EXPECT_EQ(actualValue, expectValue);
        };
        return obj->getProperty(P::key).and_then(P::cast).map(onCastSuccess);
    };

    cmd->execute().and_then(onSuccess).map_error(onError);
}

void checkExecuteFail(const otg::AbstractObjectPtr& obj, otg::AbstractCommandPtr& cmd)
{
    using namespace otg;

    const auto onError = [](const ExceptionError&) {
        SUCCEED();
    };

    const auto onSuccess = [&obj, &cmd]() {
        FAIL() << "For object \""  //
            + std::string{ typeid(*obj).name() }  //
            + "\" command \"" + std::string{ typeid(*cmd).name() }  //
        + "\" can be executed";
    };

    cmd->execute().map(onSuccess).map_error(onError);
}

}  // namespace detail

TEST(tb_main, objectBunkerInit)
{
    const auto obj = std::make_shared<otg::ObjectBunker>();

    detail::checkExistingProperty(obj, otg::PositionProperty::key);
    detail::checkExistingProperty(obj, otg::HealthProperty::key);
    detail::checkExistingProperty(obj, otg::FuelProperty::key);
    detail::checkExistingProperty(obj, otg::AmmoProperty::key);
    detail::checkExistingProperty(obj, otg::DirectionProperty::key);

    detail::checkMissingProperty(obj, otg::VelocityProperty::key);
    detail::checkMissingProperty(obj, otg::VelocityRotateProperty::key);
}

TEST(tb_main, objectTankInit)
{
    const auto obj = std::make_shared<otg::ObjectTank>();
    detail::checkExistingProperty(obj, otg::PositionProperty::key);
    detail::checkExistingProperty(obj, otg::VelocityProperty::key);
    detail::checkExistingProperty(obj, otg::HealthProperty::key);
    detail::checkExistingProperty(obj, otg::FuelProperty::key);
    detail::checkExistingProperty(obj, otg::AmmoProperty::key);
    detail::checkExistingProperty(obj, otg::DirectionProperty::key);
    detail::checkExistingProperty(obj, otg::VelocityRotateProperty::key);
}

TEST(tb_main, objectTreeInit)
{
    const auto obj = std::make_shared<otg::ObjectTree>();
    detail::checkExistingProperty(obj, otg::PositionProperty::key);
    detail::checkExistingProperty(obj, otg::HealthProperty::key);

    detail::checkMissingProperty(obj, otg::VelocityProperty::key);
    detail::checkMissingProperty(obj, otg::FuelProperty::key);
    detail::checkMissingProperty(obj, otg::AmmoProperty::key);
    detail::checkMissingProperty(obj, otg::DirectionProperty::key);
    detail::checkMissingProperty(obj, otg::VelocityRotateProperty::key);
}

TEST(tb_main, move)
{
    using namespace otg;

    const PositionProperty::type beginPosition{ 12, 5 };
    const PositionProperty::type expectPosition{ 5, 8 };
    const PositionProperty::type diffPosition = expectPosition - beginPosition;
    const VelocityProperty::type velocity{ diffPosition.x,diffPosition.y };

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();
    AbstractAdapterMovablePtr adapterMovableTank = std::make_shared<AdapterMovable>(tank);
    AbstractCommandPtr commandMovableTank = std::make_shared<CommandMovable>(adapterMovableTank);

    detail::checkSetProperty(tank, PositionProperty::key, beginPosition);
    detail::checkSetProperty(tank, VelocityProperty::key, velocity);
    detail::checkExecute<PositionProperty>(tank, commandMovableTank, expectPosition);

    AbstractObjectPtr bunker = std::make_shared<ObjectBunker>();
    AbstractAdapterMovablePtr adapterMovableBunker = std::make_shared<AdapterMovable>(bunker);
    AbstractCommandPtr commandMovableBunker = std::make_shared<CommandMovable>(adapterMovableBunker);
    detail::checkExecuteFail(bunker, commandMovableBunker);

    AbstractObjectPtr tree = std::make_shared<ObjectTree>();
    AbstractAdapterMovablePtr adapterMovableTree = std::make_shared<AdapterMovable>(tree);
    AbstractCommandPtr commandMovableTree = std::make_shared<CommandMovable>(adapterMovableTree);
    detail::checkExecuteFail(tree, commandMovableTree);

}

TEST(tb_main, rotate)
{
    using namespace otg;

    DirectionProperty::type beginDirection{ Angel::twoPi / 4 };
    DirectionProperty::type expectDirection{ Angel::twoPi / 8 };
    DirectionProperty::type diffDirection = expectDirection - beginDirection;
    VelocityRotateProperty::type velocityRotate{ diffDirection };

    AbstractObjectPtr tank = std::make_shared<ObjectTank>();
    AbstractAdapterRotablePtr adapterRotateTank = std::make_shared<AdapterRotable>(tank);
    AbstractCommandPtr commandRotateTank = std::make_shared<CommandRotable>(adapterRotateTank);

    detail::checkSetProperty(tank, DirectionProperty::key, beginDirection);
    detail::checkSetProperty(tank, VelocityRotateProperty::key, velocityRotate);
    detail::checkExecute<DirectionProperty>(tank, commandRotateTank, expectDirection);

    AbstractObjectPtr bunker = std::make_shared<ObjectBunker>();
    AbstractAdapterRotablePtr adapterRotateBunker = std::make_shared<AdapterRotable>(bunker);
    AbstractCommandPtr commandRotateBunker = std::make_shared<CommandRotable>(adapterRotateBunker);
    detail::checkExecuteFail(bunker, commandRotateBunker);

    AbstractObjectPtr tree = std::make_shared<ObjectTree>();
    AbstractAdapterRotablePtr adapterRotateTree = std::make_shared<AdapterRotable>(tree);
    AbstractCommandPtr commandRotateTree = std::make_shared<CommandRotable>(adapterRotateTree);
    detail::checkExecuteFail(tree, commandRotateTree);
}

TEST(tb_main, worker)
{
    using namespace otg;

    std::vector<std::tuple<PositionProperty::type, AbstractObjectPtr, AbstractCommandPtr>> tasks;

    for (int i = 0; i < 10; ++i)
    {
        const PositionProperty::type beginPosition{ i + 5, i + 10 };
        const PositionProperty::type expectPosition{ i, i * 2 };
        const PositionProperty::type diffPosition = expectPosition - beginPosition;
        const VelocityProperty::type velocity{ diffPosition.x,diffPosition.y };

        AbstractObjectPtr tank = std::make_shared<ObjectTank>();
        tank->setProperty(PositionProperty::key, beginPosition);
        tank->setProperty(VelocityProperty::key, velocity);
        AbstractAdapterMovablePtr adapterMovable = std::make_shared<AdapterMovable>(tank);
        AbstractCommandPtr commandMovable = std::make_shared<CommandMovable>(adapterMovable);

        tasks.emplace_back(expectPosition, tank, commandMovable);
    }

    // Scope is needed to call destructor of worker on exit
    // In the destructor thread of execution is joined
    {
        CommandWorker worker;

        EXPECT_TRUE(worker.isRunning());

        worker.push(std::make_shared<CommandStop>());

        // Pushing command that will execute with an error
        AbstractObjectPtr tree = std::make_shared<ObjectTree>();
        AbstractAdapterMovablePtr errorAdapterMovable = std::make_shared<AdapterMovable>(tree);
        AbstractCommandPtr errorCommandMovable = std::make_shared<CommandMovable>(errorAdapterMovable);
        worker.push(errorCommandMovable);

        for (auto& [pos, obj, cmd] : tasks)
        {
            worker.push(cmd);
        }

        worker.push(std::make_shared<CommandInterrupt>());

        // Pushing commands to be interrupted
        for (const auto& [pos, obj, cmd] : tasks)
        {
            worker.push(cmd);
        }

        worker.start();
    }

    for (const auto& [expectPosition, obj, cmd] : tasks)
    {
        const auto onCompareResultExecute = [&expectPosition](const PositionProperty::type& actualPosition) {
            EXPECT_EQ(actualPosition, expectPosition);
        };

        const auto onError = [](const ExceptionError& error) {
            FAIL() << error.message();
        };

        obj->getProperty(PositionProperty::key).and_then(PositionProperty::cast).map(onCompareResultExecute).map_error(onError);
    }
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
