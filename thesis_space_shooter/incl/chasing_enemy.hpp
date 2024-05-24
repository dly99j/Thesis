#ifndef CHASING_ENEMY_HPP
#define CHASING_ENEMY_HPP

#include "enemy_ship.hpp"
#include "config.hpp"
#include <iostream>

namespace spsh {
    class chasing_enemy : public enemy_ship {
    public:
        explicit chasing_enemy(direction, float = 700.0f, short = 10);

        auto change_random_direction() -> bool;

        auto calculate_direction(sf::Vector2u, std::optional<sf::FloatRect>) -> void override;

    private:
        sf::Clock m_direction_timer;
    };
} // spsh

#endif //CHASING_ENEMY_HPP
