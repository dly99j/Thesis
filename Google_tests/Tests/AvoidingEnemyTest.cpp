#include "avoiding_enemy.hpp"
#include <gtest/gtest.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

class AvoidingEnemyTest : public ::testing::Test {
protected:
    std::unique_ptr<spsh::avoiding_enemy> TestObject;

    void SetUp() override {
        TestObject = std::make_unique<spsh::avoiding_enemy>(spsh::direction::stationary);
    }

    void TearDown() override {
    }
};

TEST_F(AvoidingEnemyTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 650.0f);
    EXPECT_EQ(TestObject->get_lives(), 11);
    EXPECT_TRUE(TestObject->is_alive());
}

TEST_F(AvoidingEnemyTest, IsBulletCloseTest) {
    sf::Vector2u screen_dimensions(1280, 960);
    sf::FloatRect bullet_rect_far(1000.0f, 900.0f, 60.0f, 60.0f);
    sf::FloatRect bullet_rect_close(400.0f, 300.0f, 60.0f, 60.0f);

    TestObject->set_position(sf::Vector2f(400.0f, 300.0f));

    EXPECT_FALSE(TestObject->is_bullet_close(screen_dimensions, bullet_rect_far));

    EXPECT_TRUE(TestObject->is_bullet_close(screen_dimensions, bullet_rect_close));
}

