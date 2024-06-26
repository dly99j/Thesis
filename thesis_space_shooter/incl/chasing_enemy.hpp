#ifndef CHASING_ENEMY_HPP
#define CHASING_ENEMY_HPP

#include <iostream>
#include "config.hpp"
#include "enemy_ship.hpp"

namespace spsh {
class chasing_enemy : public enemy_ship {
   public:
    explicit chasing_enemy(direction, float = constants::chasing_enemy_speed,
                           short = constants::chasing_enemy_lives);

    auto change_random_direction() -> bool;

    auto calculate_direction(sf::Vector2u,
                             std::optional<sf::FloatRect>) -> void override;

   private:
    sf::Clock m_direction_timer;
};
}  // namespace spsh

#endif  //CHASING_ENEMY_HPP
