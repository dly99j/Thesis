#include "movable.hpp"
#include <gtest/gtest.h>
#include <SFML/Graphics/Texture.hpp>


class MovableTest : public ::testing::Test {
protected:
    std::unique_ptr<spsh::movable> TestObject;
    void SetUp() override {
        TestObject = std::make_unique<spsh::movable>(spsh::direction::stationary, 0.0f);
    }

    void TearDown() override {
    }
};

// Test case for the constructor
TEST_F(MovableTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 0.0f);
}

// Test case for the equality operator
TEST_F(MovableTest, EqualityOperatorTest) {
    spsh::movable Equal(spsh::direction::stationary, 0.0f);
    spsh::movable NotEqualDirection(spsh::direction::up, 0.0f);
    spsh::movable NotEqualSpeed(spsh::direction::stationary, 2.0f);

    spsh::movable NotEqualPosition(spsh::direction::stationary, 2.0f);
    NotEqualPosition.set_position({5.0f, 5.0f});

    EXPECT_EQ(*TestObject, Equal);
    EXPECT_NE(*TestObject, NotEqualDirection);
    EXPECT_NE(*TestObject, NotEqualSpeed);
    EXPECT_NE(*TestObject, NotEqualPosition);
}

TEST_F(MovableTest, SpeedTest) {
    EXPECT_EQ(TestObject->get_speed(), 0.0f);
    EXPECT_NE(TestObject->get_speed(), 1.0f);

    TestObject->set_speed(2.0f);

    EXPECT_EQ(TestObject->get_speed(), 2.0f);
    EXPECT_NE(TestObject->get_speed(), 0.0f);
}

TEST_F(MovableTest, DirectionTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_NE(TestObject->get_direction(), spsh::direction::up);

    TestObject->set_direction(spsh::direction::left);

    EXPECT_EQ(TestObject->get_direction(), spsh::direction::left);
    EXPECT_NE(TestObject->get_direction(), spsh::direction::stationary);
}

TEST_F(MovableTest, TextureTest) {
    sf::Texture Texture1;
    sf::Texture Texture2;
    Texture1.create(100, 100);
    Texture2.create(200, 200);

    spsh::movable EqualTexture(spsh::direction::stationary, 0.0f);
    spsh::movable NotEqualTexture(spsh::direction::stationary, 0.0f);
    EqualTexture.set_texture(Texture1);
    NotEqualTexture.set_texture(Texture2);
    TestObject->set_texture(Texture1);

    EXPECT_EQ(TestObject->get_texture_rect(), EqualTexture.get_texture_rect());
    EXPECT_NE(TestObject->get_texture_rect(), NotEqualTexture.get_texture_rect());
    EXPECT_EQ(TestObject->get_reduced_texture_rect(), EqualTexture.get_reduced_texture_rect());
    EXPECT_NE(TestObject->get_reduced_texture_rect(), NotEqualTexture.get_reduced_texture_rect());
}

TEST_F(MovableTest, MoveTest) {
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0.0f, 0.0f));

    TestObject->move(sf::Vector2f(5.0f, 0.0f));
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(5.0f, 0.0f));

    TestObject->move(sf::Vector2f(0.0f, 5.0f));
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(5.0f, 5.0f));
}

TEST_F(MovableTest, OffMapTest) {
    const auto Window = std::make_unique<sf::Vector2u>(100, 100);
    sf::Texture Texture1;
    Texture1.create(50, 50);
    TestObject->set_texture(Texture1);

    EXPECT_FALSE(TestObject->is_off_map(Window));

    TestObject->move(sf::Vector2f(-5.0f, 0.0f));

    EXPECT_TRUE(TestObject->is_off_map(Window));

    TestObject = std::make_unique<spsh::movable>(spsh::direction::stationary, 0.0f);
    TestObject->move(sf::Vector2f(0.0f, -5.0f));

    EXPECT_TRUE(TestObject->is_off_map(Window));
}
