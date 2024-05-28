#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP
#include <random>

#include "config.hpp"
#include "ship_base.hpp"

namespace spsh {
class enemy_ship : public ship_base {
   public:
    explicit enemy_ship(direction, float, short);

    virtual ~enemy_ship() = default;

    [[nodiscard]]
    auto shoot(std::optional<sf::FloatRect>)
        -> std::optional<projectile> override;

    [[nodiscard]]
    auto send_projectile_if_needed(sf::FloatRect) -> std::optional<projectile>;

    auto virtual calculate_direction(sf::Vector2u,
                                     std::optional<sf::FloatRect>) -> void = 0;

   protected:
    auto needs_to_shoot(sf::FloatRect) const -> bool;

   protected:
    sf::Clock m_enemy_clock;
    sf::Time m_time_since_alive;
    sf::Texture m_bullet_texture;

    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<int> m_dist;
};
}  // namespace spsh

#endif  //ENEMY_SHIP_HPP
