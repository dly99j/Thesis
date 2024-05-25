#include "waypoint_enemy.hpp"
#include <gtest/gtest.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class WaypointEnemyTest : public ::testing::Test {
protected:
    std::unique_ptr<spsh::waypoint_enemy> TestObject;

    void SetUp() override {
        TestObject = std::make_unique<spsh::waypoint_enemy>(spsh::direction::stationary);
    }

    void TearDown() override {
    }
};

TEST_F(WaypointEnemyTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 500.0f);
    EXPECT_EQ(TestObject->get_lives(), 12);
    EXPECT_TRUE(TestObject->is_alive());
}

TEST_F(WaypointEnemyTest, CalculateDirectionTest) {
    sf::Vector2u screen_dimensions(1280, 960);

    TestObject->set_position(sf::Vector2f(-1.0f, -1.0f));

    TestObject->calculate_direction(screen_dimensions, std::nullopt);
    auto initial_direction = TestObject->get_direction();
    EXPECT_NE(initial_direction, spsh::direction::stationary);

}
