#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP
#include "ship_base.hpp"

namespace spsh {

    class enemy_ship : public ship_base {
    public:
        explicit enemy_ship(direction, float, short = 3);

        [[nodiscard]]
        auto shoot() -> std::optional<projectile> override;

        auto send_projectile_if_needed() -> std::optional<projectile>;

    private:
        sf::Clock m_enemy_clock;
        sf::Time m_time_since_alive;
        sf::Texture m_bullet_texture;
    };

} // spsh

#endif //ENEMY_SHIP_HPP
