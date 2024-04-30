#ifndef AVOIDING_ENEMY_HPP
#define AVOIDING_ENEMY_HPP
#include "enemy_ship.hpp"
#include <iostream>
#include <cmath>

namespace spsh {

class avoiding_enemy : public enemy_ship {
public:
    explicit avoiding_enemy(direction, float = 500.0f, short = 3);

    auto change_random_direction() -> void;

    auto left_right_switch(sf::Vector2u) -> void;

    auto is_bullet_close(sf::Vector2u, std::optional<sf::FloatRect>) const -> bool;

    auto calculate_direction(sf::Vector2u, std::optional<sf::FloatRect>) -> void override;

private:
    sf::Clock m_direction_timer;
    bool m_is_going_left;
    bool m_is_going_diagonally;
    bool m_is_going_upwards;
};

} // spsh

#endif //AVOIDING_ENEMY_HPP
