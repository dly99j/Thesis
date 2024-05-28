#include "ship_base.hpp"
#include <gtest/gtest.h>
#include <SFML/Graphics/Texture.hpp>

class TestShip : public spsh::ship_base {
public:
    TestShip(spsh::direction dir, float speed, short lives)
        : ship_base(dir, speed, lives) {
    }

    std::optional<spsh::projectile> shoot(std::optional<sf::FloatRect>) override {
        return std::nullopt;
    }
};

class ShipBaseTest : public ::testing::Test {
protected:
    std::unique_ptr<TestShip> TestObject;

    void SetUp() override {
        TestObject = std::make_unique<TestShip>(spsh::direction::stationary, 0.0f, 3);
    }

    void TearDown() override {
    }
};

TEST_F(ShipBaseTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 0.0f);
    EXPECT_EQ(TestObject->get_lives(), 3);
    EXPECT_TRUE(TestObject->is_alive());
}

TEST_F(ShipBaseTest, DecreaseLifeTest) {
    TestObject->decrease_life(1);
    EXPECT_EQ(TestObject->get_lives(), 2);
    EXPECT_TRUE(TestObject->is_alive());

    TestObject->decrease_life(2);
    EXPECT_EQ(TestObject->get_lives(), 0);
    EXPECT_FALSE(TestObject->is_alive());
}

TEST_F(ShipBaseTest, IncreaseLifeTest) {
    TestObject->increase_life(2);
    EXPECT_EQ(TestObject->get_lives(), 5);
    EXPECT_TRUE(TestObject->is_alive());
}

TEST_F(ShipBaseTest, PutBackOnMapTest) {
    const auto window_size = std::make_unique<sf::Vector2u>(100, 100);
    sf::Texture texture;
    texture.create(10, 10);
    TestObject->set_texture(texture);

    TestObject->set_position(sf::Vector2f(-5.0f, 0.0f));
    EXPECT_TRUE(TestObject->is_off_map(window_size));

    TestObject->put_back_on_map(window_size);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0.0f, 0.0f));

    TestObject->set_position(sf::Vector2f(95.0f, 0.0f));
    TestObject->put_back_on_map(window_size);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(90.0f, 0.0f)); // assuming texture width is 10

    TestObject->set_position(sf::Vector2f(0.0f, 95.0f));
    TestObject->put_back_on_map(window_size);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0.0f, 90.0f)); // assuming texture height is 10
}
