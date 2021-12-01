#include <gtest/gtest.h>
#include <typeinfo>

#include "../src/commands/AbstractAdapter.cpp"
#include "../src/commands/AdapterMovable.cpp"
#include "../src/commands/AdapterRotable.cpp"
#include "../src/commands/CommandMovable.cpp"
#include "../src/commands/CommandRotable.cpp"
#include "../src/objects/Objects.cpp"
#include "../src/types/ExceptionError.cpp"
#include "../src/types/Vector.cpp"

namespace detail {

void checkExistingProperty(const otg::AbstractObjectPtr &obj, const otg::PropertyKey &key)
{
	const auto onMissing = [](const otg::ExceptionError &error) {
		FAIL() << error.message();
	};

	const auto onExist = [&obj, &key, &onMissing]() {
		obj->getProperty(key).map_error(onMissing);
		SUCCEED();
	};

	obj->setProperty(key, {}).map(onExist).map_error(onMissing);
}

void checkMissingProperty(const otg::AbstractObjectPtr &obj, const otg::PropertyKey &key)
{
	const std::string errorMessage {"Property \"" + std::string {key} + "\" exists for object " + std::string {typeid(*obj).name()}};

	const auto onExist = [&errorMessage]() {
		FAIL() << errorMessage;
	};

	const auto onMissing = [&obj, &key, &errorMessage](const otg::ExceptionError &) {
		obj->getProperty(key)
		    .map([&errorMessage](const auto &&) {
			    FAIL() << errorMessage;
		    })
		    .map_error([](const otg::ExceptionError &) {
			    SUCCEED();
		    });
	};

	obj->setProperty(key, {}).map(onExist).map_error(onMissing);
}

void checkSetProperty(const otg::AbstractObjectPtr &obj, const otg::PropertyKey &key, const otg::PropertyValue &value)
{
	obj->setProperty(key, value)
	    .map([]() {
		    SUCCEED();
	    })
	    .map_error([](const otg::ExceptionError &error) {
		    FAIL() << error.message();
	    });
}

template<class P, class T = P::type>
void checkExecute(const otg::AbstractObjectPtr &obj, otg::AbstractCommandPtr &cmd, const T &expectValue)
{
	using namespace otg;

	const auto onError = [](const ExceptionError &error) {
		FAIL() << error.message();
	};

	const auto onSuccess = [&obj, &expectValue]() {
		const auto onCastSuccess = [&expectValue](const T &actualValue) {
			EXPECT_EQ(actualValue, expectValue);
		};
		return obj->getProperty(P::key).and_then(P::cast).map(onCastSuccess);
	};

	cmd->execute().and_then(onSuccess).map_error(onError);
}

void checkExecuteFail(const otg::AbstractObjectPtr &obj, otg::AbstractCommandPtr &cmd)
{
	using namespace otg;

	const auto onError = [](const ExceptionError &) {
		SUCCEED();
	};

	const auto onSuccess = [&obj, &cmd]() {
		FAIL() << "For object \""  //
		              + std::string {typeid(*obj).name()}  //
		              + "\" command \"" + std::string {typeid(*cmd).name()}  //
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

	const PositionProperty::type beginPosition {12, 5, 0};
	const PositionProperty::type expectPosition {5, 8, 0};
	const VelocityProperty::type velocity {expectPosition - beginPosition};

	AbstractObjectPtr tank = std::make_shared<ObjectTank>();
	AbstractAdapterMovablePtr adapterMovable = std::make_shared<AdapterMovable>(tank);
	AbstractCommandPtr commandMove = std::make_shared<CommandMovable>(adapterMovable);

	detail::checkSetProperty(tank, PositionProperty::key, beginPosition);
	detail::checkSetProperty(tank, VelocityProperty::key, velocity);
	detail::checkExecute<PositionProperty>(tank, commandMove, expectPosition);

	AbstractObjectPtr bunker = std::make_shared<ObjectBunker>();
	adapterMovable->setObject(bunker);
	detail::checkExecuteFail(bunker, commandMove);

	AbstractObjectPtr tree = std::make_shared<ObjectTree>();
	adapterMovable->setObject(tree);
	detail::checkExecuteFail(tree, commandMove);
}

TEST(tb_main, rotate)
{
	using namespace otg;

	DirectionProperty::type beginDirection {0, 1, 0};
	DirectionProperty::type expectDirection {1, 1, 0};
	VelocityRotateProperty::type velocityRotate = expectDirection - beginDirection;

	AbstractObjectPtr tank = std::make_shared<ObjectTank>();
	AbstractAdapterRotablePtr adapterRotate = std::make_shared<AdapterRotable>(tank);
	AbstractCommandPtr commandRotate = std::make_shared<CommandRotable>(adapterRotate);

	detail::checkSetProperty(tank, DirectionProperty::key, beginDirection);
	detail::checkSetProperty(tank, VelocityRotateProperty::key, velocityRotate);
	detail::checkExecute<DirectionProperty>(tank, commandRotate, expectDirection);

	AbstractObjectPtr bunker = std::make_shared<ObjectBunker>();
	adapterRotate->setObject(bunker);
	detail::checkExecuteFail(bunker, commandRotate);

	AbstractObjectPtr tree = std::make_shared<ObjectTree>();
	adapterRotate->setObject(tree);
	detail::checkExecuteFail(tree, commandRotate);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
