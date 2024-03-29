#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP
#include "ship_base.hpp"

namespace spsh {
    class enemy_ship : public ship_base {
    public:
        explicit enemy_ship(direction, float, short);

        [[nodiscard]]
        auto shoot(std::optional<sf::FloatRect>) -> std::optional<projectile> override;

        [[nodiscard]]
        auto send_projectile_if_needed(sf::FloatRect) -> std::optional<projectile>;

        auto virtual calculate_direction(sf::FloatRect, sf::Vector2u) -> void = 0;

    protected:
        auto needs_to_shoot(sf::FloatRect) const -> bool;

    protected:
        sf::Clock m_enemy_clock;
        sf::Time m_time_since_alive;
        sf::Texture m_bullet_texture;
    };
} // spsh

#endif //ENEMY_SHIP_HPP
