#include "enemy_ship.hpp"
#include <gtest/gtest.h>
#include <SFML/Graphics/Texture.hpp>

class TestEnemyShip : public spsh::enemy_ship {
public:
    TestEnemyShip(const spsh::direction dir, const float speed, const short lives)
        : enemy_ship(dir, speed, lives) {
        set_texture(sf::Texture()); //it is an abstract class, doesn't have a texture by default
    }

    void calculate_direction(sf::Vector2u window_size, std::optional<sf::FloatRect> player_rect) override {
    }
};

class EnemyShipTest : public ::testing::Test {
protected:
    std::unique_ptr<TestEnemyShip> TestObject;

    void SetUp() override {
        TestObject = std::make_unique<TestEnemyShip>(spsh::direction::stationary, 100.0f, 3);
    }

    void TearDown() override {
    }
};

TEST_F(EnemyShipTest, ConstructorTest) {
    EXPECT_EQ(TestObject->get_direction(), spsh::direction::stationary);
    EXPECT_EQ(TestObject->get_position(), sf::Vector2f(0, 0));
    EXPECT_EQ(TestObject->get_speed(), 100.0f);
    EXPECT_EQ(TestObject->get_lives(), 3);
    EXPECT_TRUE(TestObject->is_alive());
}

TEST_F(EnemyShipTest, ShootTest) {
    const sf::FloatRect player_rect(50.0f, 50.0f, 50.0f, 50.0f);

    auto projectile = TestObject->shoot(player_rect);
    EXPECT_TRUE(projectile.has_value());
    if (projectile) {
        EXPECT_EQ(projectile->get_position().y, TestObject->get_position().y + TestObject->get_reduced_texture_rect().height);
        EXPECT_EQ(projectile->get_direction(), spsh::direction::down);
    }
}
