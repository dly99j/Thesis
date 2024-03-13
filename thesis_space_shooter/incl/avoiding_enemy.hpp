//
// Created by htamas on 2024.03.12..
//

#ifndef AVOIDING_ENEMY_HPP
#define AVOIDING_ENEMY_HPP
#include "enemy_ship.hpp"

namespace spsh {

    class avoiding_enemy : public enemy_ship {

    public:
        explicit avoiding_enemy(direction, float = 500.0f, short = 3);

        auto calculate_direction(sf::FloatRect, sf::Vector2u) -> void override;

    };

} // spsh

#endif //AVOIDING_ENEMY_HPP
