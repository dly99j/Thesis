#include "ship_base.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock-function-mocker.h>

class MockShipBase : public spsh::ship_base {
public:
    using ship_base::ship_base;
    MOCK_METHOD1(shoot, std::optional<spsh::projectile>(std::optional<sf::FloatRect>));
};

class ShipTest : public ::testing::Test {
protected:
    std::unique_ptr<MockShipBase> TestObject;  
    void SetUp() override {
        TestObject = std::make_unique<MockShipBase>(spsh::direction::stationary, 0.0f, 1);
    }

    void TearDown() override {
    }
};

TEST_F(ShipTest, GetLife) {
    EXPECT_EQ(TestObject->get_lives(), 1);
}

TEST_F(ShipTest, IncreaseDecreaseLife) {
    TestObject->increase_life(2);
    EXPECT_EQ(TestObject->get_lives(), 3);

    TestObject->decrease_life(1);
    EXPECT_EQ(TestObject->get_lives(), 2);
}

