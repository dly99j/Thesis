#include "chasing_enemy.hpp"
#include <gtest/gtest.h>
#include <SFML/Graphics/Texture.hpp>

class ChasingEnemyTest : public ::testing::Test {
protected:
    std::unique_ptr<spsh::chasing_enemy> TestObject;

    void SetUp() override {
        TestObject = std::make_unique<spsh::chasing_enemy>(spsh::direction::stationary);
    }

    void TearDown() override {
    }
};

TEST_F(ChasingEnemyTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 700.0f);
    EXPECT_EQ(TestObject->get_lives(), 10);
    EXPECT_TRUE(TestObject->is_alive());
}

TEST_F(ChasingEnemyTest, ChangeRandomDirectionTest) {
    EXPECT_FALSE(TestObject->change_random_direction());

    sf::Clock clock;
    while (clock.getElapsedTime() < sf::seconds(3)) {
        // Wait for enough time to pass
    }

    EXPECT_TRUE(TestObject->change_random_direction());
}

TEST_F(ChasingEnemyTest, CalculateDirectionTest) {
    sf::Vector2u screen_dimensions(1280, 960);
    sf::FloatRect player_rect(600.0f, 600.0f, 100.0f, 100.0f);

    // Case when player is on the left
    TestObject->set_position(sf::Vector2f(800.0f, 300.0f));
    TestObject->calculate_direction(screen_dimensions, player_rect);
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::left);

    // Case when player is on the right
    TestObject->set_position(sf::Vector2f(400.0f, 300.0f));
    TestObject->calculate_direction(screen_dimensions, player_rect);
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::right);

    // Case when player is close enough
    TestObject->set_position(sf::Vector2f(600.0f, 300.0f));
    TestObject->calculate_direction(screen_dimensions, player_rect);
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
}

TEST_F(ChasingEnemyTest, CalculateDirectionTestWithRandomChange) {
    sf::Vector2u screen_dimensions(1280, 960);
    sf::FloatRect player_rect(600.0f, 300.0f, 100.0f, 100.0f);

    // Simulate enough time passing for random direction change
    sf::Clock clock;
    while (clock.getElapsedTime() < sf::seconds(3)) {
        // Wait for enough time to pass
    }

    // Case when player is on the left and random direction change
    TestObject->set_position(sf::Vector2f(800.0f, 300.0f));
    TestObject->calculate_direction(screen_dimensions, player_rect);
    auto direction = TestObject->get_direction();
    EXPECT_TRUE(direction == spsh::direction::left || direction == spsh::direction::up_left || direction == spsh::direction::down_left);

    // Case when player is on the right and random direction change
    TestObject->set_position(sf::Vector2f(400.0f, 300.0f));
    TestObject->calculate_direction(screen_dimensions, player_rect);
    direction = TestObject->get_direction();
    EXPECT_TRUE(direction == spsh::direction::right || direction == spsh::direction::up_right || direction == spsh::direction::down_right);
}
