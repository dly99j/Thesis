#include "player_ship.hpp"
#include <gtest/gtest.h>

class PlayerShipTest : public ::testing::Test {
protected:
    std::unique_ptr<spsh::player_ship> TestObject;

    void SetUp() override {
        spsh::player_details test_details{
            100.0f,
            3,
            10,
            2000.0f,
            1.5f,
            5.0f,
            spsh::map::first
        };

        TestObject = std::make_unique<spsh::player_ship>(spsh::direction::stationary, test_details);
    }

    void TearDown() override {
    }
};

TEST_F(PlayerShipTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 100.0f);
    EXPECT_EQ(TestObject->get_lives(), 3);
    EXPECT_TRUE(TestObject->is_alive());
    EXPECT_EQ(TestObject->get_ammo_text().getString(), "10 rockets");
    EXPECT_EQ(TestObject->get_lifecounter_text().getString(), "3 lives");
}

TEST_F(PlayerShipTest, AddAmmoTest) {
    TestObject->add_ammo(5);
    EXPECT_EQ(TestObject->get_ammo_text().getString(), "15 rockets");
}

TEST_F(PlayerShipTest, ShootTest) {
    auto projectile = TestObject->shoot(std::nullopt);
    EXPECT_TRUE(projectile.has_value());
    if (projectile) {
        EXPECT_EQ(TestObject->get_ammo_text().getString(), "9 rockets");
    }

    for (int i = 0; i < 9; ++i) {
        std::ignore = TestObject->shoot(std::nullopt);
    }
    EXPECT_EQ(TestObject->get_ammo_text().getString(), "0 rockets");

    projectile = TestObject->shoot(std::nullopt);
    EXPECT_FALSE(projectile.has_value());
}

TEST_F(PlayerShipTest, SpeedBoostTest) {
    const auto original_speed = TestObject->get_speed();
    TestObject->start_speed_boost();
    EXPECT_GT(TestObject->get_speed(), original_speed);

    sf::Clock clock;
    while (clock.getElapsedTime() < sf::seconds(5)) {
        TestObject->handle_speed_boost();
    }

    EXPECT_EQ(TestObject->get_speed(), original_speed);
}

TEST_F(PlayerShipTest, LifeCounterTextTest) {
    EXPECT_EQ(TestObject->get_lifecounter_text().getString(), "3 lives");
    TestObject->decrease_life();
    EXPECT_EQ(TestObject->get_lifecounter_text().getString(), "2 lives");
}

TEST_F(PlayerShipTest, AmmoTextTest) {
    EXPECT_EQ(TestObject->get_ammo_text().getString(), "10 rockets");
    TestObject->add_ammo(5);
    EXPECT_EQ(TestObject->get_ammo_text().getString(), "15 rockets");
}
