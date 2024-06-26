#ifndef WAYPOINT_ENEMY_HPP
#define WAYPOINT_ENEMY_HPP
#include <iostream>
#include "enemy_ship.hpp"

namespace spsh {
class waypoint_enemy : public enemy_ship {
   public:
    explicit waypoint_enemy(direction, float = constants::waypoint_enemy_speed,
                            short = constants::waypoint_enemy_lives);

    auto calculate_direction(sf::Vector2u,
                             std::optional<sf::FloatRect>) -> void override;

   protected:
    auto generate_new_waypoint(sf::Vector2u) -> void;

    auto is_close_to_waypoint() const -> bool;

   private:
    sf::Vector2f m_waypoint;
    bool m_need_new_gen;
};
}  // namespace spsh

#endif  //WAYPOINT_ENEMY_HPP
